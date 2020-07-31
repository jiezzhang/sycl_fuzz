import os
import platform
import shutil
import subprocess
from threading import Timer
import argparse
import time
import datetime
from time import gmtime, strftime, sleep
import re
import xml.etree.ElementTree as ET
import logging
import errno
import stat
import sys
import signal
import zipfile
import psutil
#import cpuinfo  # not ready yet
FORMAT = '%(asctime)-15s %(message)s'
formatter = logging.Formatter(FORMAT)
logging.basicConfig(format=FORMAT)
logger = logging.getLogger()
logger.setLevel(logging.INFO)
fh = None


FORMAT = '%(asctime)-15s %(message)s'
logging.basicConfig(format=FORMAT)

ATG_WORK_DIR = os.environ['ATG_WORK_DIR']# os.getcwd() # "C:\\ATG_HOME"
ATG_HOME_DIR = os.environ['ATG_HOME_DIR']# os.getcwd()  # "/export/users/itaraban/work/atg"
ICS_HOME = "R:\\ics"
compilation_command_pattern = "%s -c %s -o lib%s.o lib%s.%s && " \
                              "%s -c %s -o test.o %s && " \
                              "%s %s -o test.exe test.o lib%s.o"
architectures = {
    "knl": ['avx512f', 'avx512cd', 'avx512er', 'avx512pf', 'prefetchwt1', 'fxsr', 'rdseed', 'adx', 'lzcnt', 'bmi',
            'bmi2', 'rtm', 'fma', 'rdrnd', 'f16c', 'fsgsbase', 'aes', 'pclmul', 'cx16', 'xsaveopt', 'xsave', 'movbe'],
    "skx": ['avx512f', 'avx512cd', 'avx512dq', 'avx512bw', 'avx512vl', 'pku', 'clwb'],
    "cannonlake": ['avx512ifma', 'avx512vbmi', 'sha'],
    # Bobcat architecture processor
    'btver1': ['ssse3', 'sse4a', 'lzcnt', 'popcnt', 'prfchw', 'cx16', 'fxsr']
}
current_arch = []  # cpuinfo.get_cpu_info()['flags']


def print_error(e):
    logger.error(str(e) + '\n')
    exc_type, exc_obj, exc_tb = sys.exc_info()
    fname = os.path.split(exc_tb.tb_frame.f_code.co_filename)[1]
    logger.error(" ".join(str(v) for v in [exc_type, fname, exc_tb.tb_lineno]))


def handle_remove_readonly(func, path, exc):
    exc_value = exc[1]
    if func in (os.rmdir, os.remove) and exc_value.errno == errno.EACCES:
        os.chmod(path, stat.S_IRWXU | stat.S_IRWXG | stat.S_IRWXO)  # 0777
        func(path)
    else:
        raise


killing = False



def kill_all_children(pid):
    global killing
    killing = True
    try:
        def on_terminate(p):
                 print "process", p,"terminated with exit code ", p.returncode
        print "start killing process"
        proc = psutil.Process(pid)
        all_children = proc.children(recursive=True)
        children = proc.children()
        for child in all_children:
            print "CHILD:", child
        for child in children:
            print "Send SIGTERM to ", child.pid
            """child.terminate()
            if child.is_running():
                child.kill()"""
            child.terminate()
            gone, alive = psutil.wait_procs([child], timeout=5, callback=on_terminate)
            if alive:
                 # send SIGKILL
                for p in alive:
                    print "process", p, " survived SIGTERM; trying SIGKILL"
                    p.kill()
                gone, alive = psutil.wait_procs(alive, timeout=5, callback=on_terminate)
                if alive:
                    # give up
                    for p in alive:
                        print "process", p, "survived SIGKILL; giving up"
        grandchildren = set(all_children) - set(children)
        for grandchild in grandchildren:
            if grandchild.is_running():
                print "Send SIGTERM to ", grandchild.pid
                grandchild.terminate()
                gone, alive = psutil.wait_procs([grandchild], timeout=5, callback=on_terminate)
                if alive:
                    # send SIGKILL
                    for p in alive:
                        print "process", p, " survived SIGTERM; trying SIGKILL"
                        p.kill()
                    gone, alive = psutil.wait_procs(alive, timeout=5, callback=on_terminate)
                    if alive:
                        # give up
                        for p in alive:
                            print "process", p, "survived SIGKILL; giving up"
    except Exception, e:
        logger.error("Error while killing process")
        print_error(e)

def run_command(command, env):
    proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=env, shell=True)
    timeout_sec = 300
    global killing
    killing = False
    timer = Timer(timeout_sec, kill_all_children, args=[proc.pid])# os.kill, args=[proc.pid, signal.SIGTERM]) #, proc.kill)
    timer.start()
    (output, errput) = proc.communicate()
    if timer.is_alive() and not killing:
        # Process completed naturally - cancel timer and return exit code
        timer.cancel()
        return proc.returncode, output, errput  #.split('\n')[-1]
    # Process killed by timer - raise exception
    return -1.1, "" ,""


class Runner(object):
    def __init__(self, comp, use_svn, gen, test_dir=None, build_date="latest"):
        if not os.path.exists(ATG_WORK_DIR + os.path.sep + 'logs'):
            os.makedirs(ATG_WORK_DIR + os.path.sep + 'logs')
        fh = logging.FileHandler(os.path.join(ATG_WORK_DIR, "logs", "test-" + str(os.getpid()) + ".log"))
        fh.setFormatter(formatter)
        logger.addHandler(fh)
        self.compiler = comp
        self.compiler_source_type = 'svn' if use_svn else 'ics_build'
        self.build_date = build_date
        if not use_svn and "ICS_ARCHIVE_ROOT" not in os.environ:
            raise Exception("ICS_ARCHIVE_ROOT variable not set")
        if platform.system() == "Windows":
            self.os_short = "win"
        elif platform.system() == "Linux":
            self.os_short = "linux"
        else:
            raise Exception("Unsupported system %s" % platform.system())
            
        if not os.path.exists(os.path.join(ATG_WORK_DIR, "tools")):
            if platform.system() == "Windows":
                tools_zip = os.path.join(ATG_HOME_DIR, "tools-win.zip")
            elif platform.system() == "Linux":
                tools_zip = os.path.join(ATG_HOME_DIR, "tools-linux.zip")
            else:
                raise Exception("Unsupported system %s" % platform.system())

            zp = zipfile.ZipFile(tools_zip, 'r')
            zp.extractall(ATG_WORK_DIR + os.path.sep + "tools")
            zp.close()
            if platform.system() != "Windows":
                for root, dirs, files in os.walk(ATG_WORK_DIR + os.path.sep + "tools", topdown=False):
                    for name in files:
                        os.chmod(os.path.join(root, name) , stat.S_IRWXU | stat.S_IRWXG | stat.S_IRWXO)
        
        tree = ET.parse(ATG_HOME_DIR + os.path.sep + "config-" + self.os_short + ".xml")
        root = tree.getroot()
        generators = root.find("generators")
        self.generator = gen
        self.lib_lang = "c"
        for generator in generators:
            if generator.attrib['name'] == gen:
                if "hasInput" in generator.attrib:
                    self.run_input = generator.attrib['hasInput'] == "true"
                else:
                    self.run_input = False
                self.generator_command = generator.attrib['command']
                if "Lang" in generator.attrib:
                    if generator.attrib["Lang"] == "IR":
                        self.lang = "ll"
                    elif generator.attrib["Lang"] == "DPCPP":
                        self.lang = "hpp"
                    else:
                        raise Exception("Unsupported test language")

                else:
                    self.lang = self.lib_lang
                break
        else:
            raise Exception("No such generator in config file")
        compilers = root.find("compilers")
        for compiler in compilers:
            if compiler.attrib['name'] == comp:
                self.compilerC = compiler.attrib["compilerC"]
                self.compilerCpp = compiler.attrib["compilerCpp"]
                self.compiler_arch = {}
                archs = [attr for attr in compiler.attrib if attr.startswith("arch_")]
                for arch in archs:
                    self.compiler_arch["_".join(arch.split("_")[1:])] = compiler.attrib[arch]
                if "linkerLTO" in compiler.attrib:
                    self.linkerLTO = compiler.attrib['linkerLTO']
                else:
                    self.linkerLTO = ""
                if not use_svn:
                    self.bin_path = compiler.attrib["ICS_bin_path"]
                    self.lib_path = compiler.attrib["ICS_lib_path"]
                    if platform.system() == "Windows":
                        self.bin_path = self.bin_path.replace("/", "\\")
                        self.lib_path = self.lib_path.replace("/", "\\")
                        self.lib_path = self.lib_path.replace("linux", "windows")
                        self.lib_path = self.lib_path.replace("lin", "win")
                if comp == 'xmain':
                    self.project = "xmain"
                    self.config = "xmainefi2" + self.os_short
                elif comp.startswith('clang'):
                    self.project = "llorg-trunk"
                    self.config = "llorgefi2" + self.os_short
                else:
                    if not use_svn:
                        raise Exception("Unknown project for ics builds")
                break
        else:
            raise Exception("No Such compiler in config file")
        self.TEST_DIRECTORY = ATG_WORK_DIR + os.path.sep + "testing" + os.path.sep + "testing_" + str(os.getpid())
        if test_dir and os.path.exists(test_dir):
            self.test_dir = test_dir
        else:
            self.test_dir = self.TEST_DIRECTORY + os.path.sep + "test"
            os.makedirs(self.test_dir)
        for file in os.listdir(ATG_HOME_DIR + os.path.sep + "test"):
            shutil.copy(os.path.join(ATG_HOME_DIR, "test", file), self.test_dir)
        if test_dir is None:
            shutil.copytree(os.path.join(ATG_WORK_DIR, "tools", "generators"), os.path.join(self.test_dir, "..", "generators"))
        self.clear_env = os.environ.copy()
        self.my_env = self.clear_env.copy()
        self.status = "passed"
        self.opt_last = ""

    def config_compiler(self):
        build_bin_directory = ""
        build_lib_directory = ""
        if self.compiler_source_type == 'svn':
            try:
                builds = os.listdir(ATG_WORK_DIR + os.path.sep + "builds")
                build_revisions = [int(x.split("_")[1]) for x in builds if x.startswith('build') and x.endswith("DONE")]
                build_revisions.sort()
                last_svn_build_directory = os.path.join(ATG_WORK_DIR, "builds",
                                                        "build_" + str(build_revisions[-1]) + "_DONE")
                if os.path.exists(last_svn_build_directory):
                    build_directory = last_svn_build_directory # self.TEST_DIRECTORY + os.path.sep + "build_" + str(build_revisions[-1])
                    logger.info("Set build to " + str(build_revisions[-1]))
                    if not os.path.exists(build_directory):
                        for directory in os.listdir(self.TEST_DIRECTORY):
                            if directory.startswith("build"):
                                shutil.rmtree(os.path.join(self.TEST_DIRECTORY, directory),
                                              ignore_errors=False, onerror=handle_remove_readonly)
                        shutil.copytree(last_svn_build_directory, build_directory)
                else:
                    raise Exception("Error in last build")
            except Exception:
                raise Exception("Error while finding build")
            build_bin_directory = build_directory + os.path.sep + "bin"
            build_lib_directory = os.path.join(build_directory, "lib")

        else:
            if self.build_date == "TRY_LATEST":
                ics_build_date = strftime("%Y%m%d_000000", gmtime())
            else:
                ics_build_date = self.build_date
            build_directory = os.path.join(os.environ['ICS_ARCHIVE_ROOT'], "deploy_" + self.project, self.config,
                                           ics_build_date, "build", self.os_short + "_prod")
            build_bin_directory = os.path.join(build_directory, self.bin_path)
            build_lib_directory = os.path.join(build_directory, self.lib_path)
            logger.info("Set compiler date:%s" % ics_build_date)
            # print build_bin_directory, build_lib_directory

        self.my_env = self.clear_env.copy()
        self.my_env['PATH'] = self.test_dir + os.pathsep + ATG_WORK_DIR + os.path.sep + "tools" + os.pathsep + self.my_env['PATH']

        self.my_env['PATH'] = self.TEST_DIRECTORY + os.pathsep + self.my_env['PATH']

        self.my_env['PATH'] = build_bin_directory + os.pathsep + self.my_env['PATH']


        if 'LD_LIBRARY_PATH' in self.my_env:
            self.my_env['LD_LIBRARY_PATH'] = build_lib_directory + os.pathsep + self.my_env["LD_LIBRARY_PATH"]
        else:
            self.my_env['LD_LIBRARY_PATH'] = build_lib_directory
        if 'LIBRARY_PATH' in self.my_env:
            self.my_env['LIBRARY_PATH'] = build_lib_directory + os.pathsep + self.my_env["LIBRARY_PATH"]
        else:
            self.my_env['LIBRARY_PATH'] = build_lib_directory
        # Won't copy OCL_ICD_FILENAMES. Use env variable instead        

        compiler_executable = self.compilerC.split(" ")[0]
        if not os.path.exists(os.path.join(build_bin_directory, compiler_executable)) and \
                not os.path.exists(os.path.join(build_bin_directory, compiler_executable + ".exe")):
            logger.error("Compiler executable not found")
            time.sleep(600)
        else:
            logger.info("Compiler configured")

    def run_generator(self):
        os.chdir(self.test_dir)
        if os.path.exists(os.path.join(self.test_dir, 'test.c')):
            os.remove(os.path.join(self.test_dir, 'test.c'))
        if os.path.exists(os.path.join(self.test_dir, 'test.cpp')):
            os.remove(os.path.join(self.test_dir, 'test.cpp'))
        if os.path.exists(os.path.join(self.test_dir, 'input.txt')):
            os.remove(os.path.join(self.test_dir, 'input.txt'))
        if os.path.exists(os.path.join(self.test_dir, 'kernel_impl.hpp')):
            os.remove(os.path.join(self.test_dir, 'kernel_impl.hpp'))
        gen_command = "cd %s && " % os.path.join(self.test_dir, "..", "generators") + self.generator_command
        (status, out_data, err_data) = run_command(gen_command, env=self.my_env)
        while status != 0:
            logger.error("Time limit error while generating test")
            time.sleep(6)
            (status, out_data, err_data) = run_command(gen_command, env=self.my_env)
        #p = subprocess.Popen("cd %s && " % os.path.join("tools", "generators") +
        #                     self.generator_command,
        #                     stdout=subprocess.PIPE, env=self.my_env, shell=True)
        input_file_path = os.path.join(self.test_dir, "..", "generators", "input.txt")
        if os.path.exists(input_file_path):
            shutil.move(input_file_path, self.test_dir + os.path.sep + "input.txt")
            self.run_input = True
        else:
            self.run_input = False
        if re.search("This is C\+\+", out_data):
            self.lib_lang = "cpp"
        elif re.search("This is DPCPP", out_data):
            self.lib_lang = "hpp"
        else:
            self.lib_lang = "c"
        if self.lang == "c" or self.lang == "cpp" or self.lang == "hpp":
            self.lang = self.lib_lang
        if self.lang == "ll":
            out_data = out_data.replace("\r\n", "\n")
        if re.search("dpcpp", self.generator):
            self.test_file_name = 'kernel_impl' + self.lang
            test_file = open(os.path.join(self.test_dir, self.test_file_name), "wb")
        else:
            self.test_file_name = 'test.' + self.lang
            test_file = open(os.path.join(self.test_dir, self.test_file_name), "wb")
        test_file.write(out_data)
        test_file.close()
        logger.info("Test generated(" + self.generator + ")")

    def bisect(self, error_type, compiler, test_name, opt, answer, run_test_command):
        logger.info("Bisect started for " + error_type)
        last_opt = "Segmentation_fault"
        #print "BISECT"
        #sys.exit()
        if "flto" in opt:
            bisect_do_link = True
        else:
            bisect_do_link = False
        if bisect_do_link:
            if self.linkerLTO:
                link_bisect = "-Wl,-mllvm,-opt-bisect-limit=%d"
            else:
                link_bisect = "-Wl,-plugin-opt,-opt-bisect-limit=%d"
        else:
            link_bisect = ""
        compilation_command = "%s -c %s -o test.o %s " % (compiler, opt, test_name)
        compilation_bisect = "-mllvm -opt-bisect-limit=%d"
        link_command = "%s %s -o test.exe test.o lib%s.o " % (compiler, opt, self.lib_lang)

        # process compfail as last pass before error
        if error_type == "compfail":
            full_command = (compilation_command + compilation_bisect + " && " + link_command) % -1
            if bisect_do_link:
                full_command = (full_command + link_bisect) % -1
            (status, out, err) = run_command(full_command, env=self.my_env)
            if status != 0:
                passes = re.findall("BISECT: running pass \((\w*)\) ([\w ]*)", err)
                if len(passes) == 0:
                    return "Front_End"
                last_opt = passes[-1][1]
                for i in [" ", ">", "/", "'", ',']:
                    last_opt = last_opt.replace(i, "_")
                logger.info("Test compfails at " + last_opt[:15])
                return last_opt[:10]

        # Get compilation bisect len
        (status, out, err) = run_command((compilation_command + compilation_bisect) % 0, env=self.my_env)
        zero_passes = re.findall("BISECT: NOT running pass \((\w*)\) ([\w ]*)", err)
        (status, out, err) = run_command((compilation_command + compilation_bisect) % -1, env=self.my_env)
        minus_passes = re.findall("BISECT: running pass \((\w*)\) ([\w ]*)", err)
        compilation_bisect_len = max(int(zero_passes[-1][0]), int(minus_passes[-1][0]))

        if bisect_do_link:
            run_command(compilation_command)
            (status, out, err) = run_command((link_command + link_bisect) % 0, env=self.my_env)
            zero_passes = re.findall("BISECT: NOT running pass \((\w*)\) ([\w ]*)", err)
            (status, out, err) = run_command((link_command + link_bisect) % -1, env=self.my_env)
            minus_passes = re.findall("BISECT: running pass \((\w*)\) ([\w ]*)", err)
            link_bisect_len = max(int(zero_passes[-1][0]), int(minus_passes[-1][0]))
        else:
            link_bisect_len = 0
        # p = subprocess.Popen(bisect_command % l, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        #                     env=self.my_env, shell=True)
        # (out_data, err_data) = p.communicate()
        # (status, out, err) = run_command(bisect_command % l, env=self.my_env)
        # passes = re.findall("BISECT: NOT running pass \((\w*)\) ([\w ]*)", err
        # if bisect_do_link:
        #     compilation_bisect_len = [i for i in range(len(passes)) if passes[i][0] == "1"][1]
        # else:
        #    compilation_bisect_len = len(passes)
        # if error_type == "compfail":
        # last_opt = passes[-1][1].replace(" ", "_")  # first after PASS in bisect
        # if error_type == "runfail":
        # (status, out, err) = run_command(bisect_command % l_2, env=self.my_env)
        # passes_2 = re.findall("BISECT: running pass \((\w*)\) ([\w ]*)", err)
        a = 0
        error_in_linkage = False
        if bisect_do_link:
            # check where is error:
            (return_code, test_answer, err) = run_command((compilation_command + " && " +
                                                          link_command + link_bisect) % 0, env=self.my_env)
            if run_test_command:
                (return_code, test_answer, err) = run_command(run_test_command, env=self.my_env)
            if return_code == 0 and (answer is None or test_answer == answer):
                error_in_linkage = True
            if error_in_linkage:
                b = link_bisect_len
                bisect_command = compilation_command + " && " + link_command + link_bisect
            else:
                b = compilation_bisect_len
                bisect_command = compilation_command + compilation_bisect + " && " + link_command
        else:
            b = compilation_bisect_len
            bisect_command = compilation_command + compilation_bisect + " && " + link_command
        # start bisect
        while b - a > 1:
            c = (a + b) / 2
            (return_code, test_answer, err) = run_command(bisect_command % c,
                                                   env=self.my_env)
            passes = re.findall("BISECT: running pass \((\w*)\) ([\w ]*)", err)
            c = int(passes[-1][0])
            logger.info("Bisect trying optimization " + str(c) + ": " + passes[-1][1])
            if run_test_command:
                (return_code, test_answer, err) = run_command(run_test_command, env=self.my_env)
            if return_code == 0 and (answer is None or test_answer == answer):
                a = c
            else:
                b = c
        if b == 1:
            last_opt = "strange_error_at_0_opt"
        else:
            (status, out, err) = run_command(bisect_command % b, env=self.my_env)
            passes = re.findall("BISECT: running pass \((\w*)\) ([\w ]*)", err)
            last_opt = passes[-1][1]
            for i in [" ", ">", "/", "'", ',']:
                last_opt = last_opt.replace(i, "_")
            if error_in_linkage:
                last_opt = "LTO_" + last_opt
        logger.info("Bisect ended at " + last_opt[:15])
        return last_opt[:10]

    def check_options(self, compiler, test_name, opt, arch=None, flto=False, answer=0):
        opt_name = opt.replace("-", "")
        status = "passed"
        last_opt = ""
        if self.run_input:
            input_args = " < input.txt"
        else:
            input_args = ""
        if arch is not None:
            opt = opt + " " + self.compiler_arch[arch]
            opt_name = opt_name + "_" + arch
            if set(architectures[arch]) & set(current_arch) != set(architectures[arch]):
                sde = "sde -" + arch + " -- "
            else:
                sde = ''
        else:
            sde = ""
            opt = opt + " " + self.compiler_arch["native"]
        if flto:
            opt = opt + " -flto " + self.linkerLTO
            opt_name = opt_name + "_flto"
        logger.info("Checking test at " + opt)
        opt_o0 = opt.replace("O1", "O0").replace("O2", "O0").replace("O3", "O0")
        """compilation command"""
        command = compilation_command_pattern % (compiler, opt_o0, self.lib_lang, self.lib_lang, self.lib_lang,
                                                 compiler, opt, test_name,
                                                 compiler, opt, self.lib_lang)

        return_code, compilation_output, err_output = run_command(command=command, env=self.my_env)
        if return_code == -1.1:
            logger.error("compilation timeout")
            last_opt = ''
            status = 'compilation_timeout'
        else:
            if return_code:
                last_opt = self.bisect('compfail', compiler, test_name, opt, answer=None, run_test_command=None)
                status = "compfail"
            else:
                return_code, test_answer, err_output = run_command(sde + "test.exe" + input_args, env=self.my_env)
                if return_code == -1.1:
                    logger.error("run timeout")
                    last_opt = ''
                    status = 'run_timeout'
                else:
                    if return_code or answer != test_answer:
                        last_opt = self.bisect('runfail', compiler, test_name, opt, answer,
                                           run_test_command=sde + "test.exe" + input_args)
                        status = "runfail"
        self.status = status
        self.opt_last = opt_name + ";" + last_opt
        return status, opt_name + last_opt

    def run_test(self, test_name='test', run_input=False):
        if test_name == 'test':
            logger.info("Start testing generated test on " + self.compiler)
        elif test_name.startswith('REDUCED-'):
            logger.info("Start testing reduced test on " + self.compiler)
        else:
            logger.info("Start testing " + test_name)
        test_name = test_name + "." + self.lang
        os.chdir(self.test_dir)
        if run_input:
            self.run_input = run_input
        if not os.path.exists("input.txt"):
            self.run_input = False
        if self.run_input:
            input_args = " < input.txt"
        else:
            input_args = ""
        compiler = self.compilerC if self.lib_lang == "c" else self.compilerCpp
        null_command_comp = compilation_command_pattern % (compiler, " -O0 ", self.lib_lang, self.lib_lang, self.lib_lang,
                                                      compiler, " -O0 ", test_name,
                                                      compiler, "-O0", self.lib_lang)
        null_command_exec = "test.exe" + input_args
        status, true_answer, err_output = run_command(null_command_comp, env=self.my_env)
        if status != 0:
            os.chdir(ATG_WORK_DIR)
            logger.info("Test is invalid")
            self.opt_last = "O0;"
            return "invalid"
        status, true_answer, err_output = run_command(null_command_exec, env=self.my_env)
        if status != 0:
            os.chdir(ATG_WORK_DIR)
            logger.info("Test is invalid")
            self.opt_last = "O0;"
            return "invalid"
        """Simple"""
        for opt in ["-O1", "-O2", "-O3"]:
            self.check_options(compiler, test_name, opt, answer=true_answer)
            if self.status != "passed":
                os.chdir(ATG_WORK_DIR)
                return self.status

        """SKX"""
        for opt in ["-O0", "-O1", "-O2", "-O3"]:
            self.check_options(compiler, test_name, opt, "skx", answer=true_answer)
            if self.status != "passed":
                os.chdir(ATG_WORK_DIR)
                return self.status
        if False:
            """LTO"""
            for opt in ["-O0", "-O1", "-O2", "-O3"]:
                self.check_options(compiler, test_name, opt, flto=True, answer=true_answer)
                if self.status != "passed":
                    os.chdir(ATG_WORK_DIR)
                    return self.status
        os.chdir(ATG_WORK_DIR)
        return 'passed'

    def reduce_test(self, test_name='test'):
        if self.lang == "ll":
            return False
        compiler = self.compilerC if self.lib_lang == "c" else self.compilerCpp
        reduce_compilation_step = "%s -c %s -o test.o -Werror $1 && %s %s -o test.exe test.o lib%s.o -Werror "
        wrong_args = self.opt_last.split(";")[0]
        correct_line = " || exit 0\n"
        wrong_line = " && exit 0\n"
        if self.run_input:
            input_args = " < input.txt"
        else:
            input_args = ""
        wrong_opt = "-" + wrong_args.split("_")[0]
        sde = ""
        if wrong_args.find("_") > 0:
            additions = wrong_args.split("_")
            for i in range(len(additions) - 1):
                if additions[i + 1] == "flto":
                    wrong_opt += " -flto"
                else:
                    sde = "sde -" + additions[i + 1] + " -- "
                    wrong_opt += " " + self.compiler_arch[additions[i + 1]]
        if sde == '':
            wrong_opt += " " + self.compiler_arch['native']
        # create reduce.sh
        script = open(os.path.join(self.test_dir, "reduce.sh"), "w")
        # compile base
        script.write((reduce_compilation_step + correct_line) % (compiler, "-O0",
                                                                   compiler, "-O0", self.lang))
        if self.status == 'runfail':
            # add diff to reduce.sh
            script.write("test.exe" + input_args + " > true" + correct_line)
            script.write((reduce_compilation_step + correct_line) % (compiler, wrong_opt,
                                                                   compiler, wrong_opt, self.lang))
            script.write(sde + "test.exe" + input_args + "> false && diff true false" + wrong_line)
        elif self.status == "compfail":
            # compile wrong
            script.write((reduce_compilation_step + wrong_line) % (compiler, wrong_opt,
                                                                       compiler, wrong_opt, self.lang))
        else:
            print_error("unknown status of error in ireduce step")
            return False
        script.write("exit 1\n")
        script.close()
        if test_name == 'test':
            logger.info("Start reducing generated test")
        else:
            logger.info("Start reducing " + test_name)
        test_name = test_name + "." + self.lang
        return_code, ireduce_output, ireduce_output = \
            run_command("cd " + self.test_dir + " && ireduce --oracle reduce.sh " + test_name, env=self.my_env)
        if return_code != 0:
            logger.error("Error while reducing")
            return False
        return True

    def save_test(self, test_name='test'):
        type_error = self.status
        timestamp = datetime.datetime.fromtimestamp(time.time()).strftime('%Y_%m_%d.%H_%M_%S')
        type_dir = os.path.join(ATG_HOME_DIR, "fails", self.compiler, type_error)
        if self.opt_last.endswith(";"):
            type_dir = os.path.join(type_dir, self.opt_last[:-1], timestamp)
        else:
            type_dir = os.path.join(type_dir, self.opt_last.split(";")[0], self.opt_last.split(";")[1], timestamp)
        logger.info("Saving " + test_name + " to " + type_dir)
        if not os.path.exists(type_dir):
            os.makedirs(type_dir)
            shutil.copy(os.path.join(self.test_dir, test_name + '.' + self.lang), os.path.join(type_dir, timestamp + '.' + self.lang))
            if self.run_input:
                shutil.copy(self.test_dir + os.path.sep + "input.txt", type_dir)
            #shutil.rmtree(self.test_dir, ignore_errors=False, onerror=handle_remove_readonly)


def main():
    """parse arguments and options"""
    parser = argparse.ArgumentParser(description='Automatic Test Generator: test runner')
    parser.add_argument('-c', dest='compiler', default='clang', help='type of compiler for ATG. Supported: clang, clang_m32, icx')
    parser.add_argument('-g', dest='generator', default='', help='type of test generator')
    parser.add_argument('-d', '--date', dest='build_date', default='latest', help='set date for archive builds, use "TRY_LATEST" for using latest date. "latest" build is used by default')
    parser.add_argument('--use-svn', dest='use_svn', action='store_true', help='enable svn usage instead of ics_builds')
    parser.add_argument('--version', action='version', version='%(atg) 0.9')
    args = parser.parse_args()
    runner = Runner(args.compiler, args.use_svn, args.generator, build_date=args.build_date)
    while True:
        try:
            """check build"""
            runner.config_compiler()
            """generate test"""
            runner.run_generator()
            """run test"""
            test_result = runner.run_test()
            """check test"""
            if test_result != 'passed' and test_result != 'invalid':
                if test_result == 'compfail' or test_result == 'runfail':
                    if runner.reduce_test():
                        old_opt = runner.opt_last.split(";")[1]
                        retest_result = runner.run_test(test_name="REDUCED-test")
                        runner.save_test("REDUCED-test")
                        if retest_result == test_result and old_opt == runner.opt_last.split(";")[1]:
                            continue
                # (test_result, opt_last) = runner.run_test()
                if test_result != 'passed':
                    runner.save_test()
        except Exception, e:
            print_error(e)
            runner.save_test()
            time.sleep(60)

if __name__ == "__main__":
    main()
