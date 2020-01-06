import os
import shutil
import sys
import platform
import time
import errno
import stat
import re
import subprocess
import argparse
import zipfile
import logging
import csv
import atg_test

FORMAT = '%(asctime)-15s %(message)s'
formatter = logging.Formatter(FORMAT)
logging.basicConfig(format=FORMAT)
fh = logging.FileHandler("core.log")
fh.setFormatter(formatter)
logger = logging.getLogger()
logger.setLevel(logging.INFO)
logger.addHandler(fh)


LLVM_SVN_PATH = 'http://llvm.org/svn/llvm-project/llvm/trunk'
CLANG_SVN_PATH = 'http://llvm.org/svn/llvm-project/cfe/trunk'
LLD_SVN_PATH = 'http://llvm.org/svn/llvm-project/lld/trunk'
ATG_WORK_DIR = os.environ['ATG_WORK_DIR']# os.getcwd() # "C:\\ATG_HOME"
ATG_HOME_DIR = os.environ['ATG_HOME_DIR']# os.getcwd()  # "/export/users/itaraban/work/atg"


def print_error(e):
    logger.error(str(e) + '\n')
    exc_type, exc_obj, exc_tb = sys.exc_info()
    fname = os.path.split(exc_tb.tb_frame.f_code.co_filename)[1]
    logger.error(str(exc_type) + str(fname) + str(exc_tb.tb_lineno))


def handle_remove_readonly(func, path, exc):
    exc_value = exc[1]
    if func in (os.rmdir, os.remove) and exc_value.errno == errno.EACCES:
        os.chmod(path, stat.S_IRWXU | stat.S_IRWXG | stat.S_IRWXO)  # 0777
        func(path)
    else:
        raise


def get_last_revision_number():
    # my_env = os.environ.copy()
    p = subprocess.Popen("svn info %s " % LLVM_SVN_PATH,
                         stdout=subprocess.PIPE, shell=True)
    (output, err) = p.communicate()
    #print output
    g = re.search("Revision: (\\w*)", output)
    if g is None:
        raise Exception("error while checking revision number")

    last_revision = int(g.group(1))
    return last_revision


class ATG(object):
    def __init__(self, compiler, use_svn, version, number_threads, is_build):
        self.compiler = compiler
        self.compiler_source_type = 'svn' if use_svn else 'ics_build'
        self.compiler_current_version = int(version) if use_svn else version
        if version == '0' and use_svn:
            self.compiler_current_version = get_last_revision_number() - 1
        self.threads = int(number_threads)
        self.BUILD_DIRECTORY = ATG_WORK_DIR + os.path.sep + "builds"
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

        if is_build and not os.path.exists(self.BUILD_DIRECTORY):
            os.makedirs(self.BUILD_DIRECTORY)
        """else:
            llvm_dir = self.BUILD_DIRECTORY + os.path.sep + "llvm"
            if os.path.exists(llvm_dir):
                shutil.rmtree(llvm_dir, ignore_errors=False, onerror=handle_remove_readonly)
                pass"""

    def get_svn_revision(self, revision):
        llvm_dir = self.BUILD_DIRECTORY + os.path.sep + "llvm"
        clang_dir = llvm_dir + os.path.sep + "tools" + os.path.sep + "clang"
        lld_dir = llvm_dir + os.path.sep + "tools" + os.path.sep + "lld"
        my_env = os.environ.copy()
        if not os.path.exists(llvm_dir):
            try:
                os.makedirs(llvm_dir)
                logger.info("Start checkout llvm")
                p = subprocess.Popen("svn co --quiet -r %d %s %s" % (revision, LLVM_SVN_PATH, llvm_dir),
                                     env=my_env, shell=True)
                p.wait()
                p = subprocess.Popen("svn co --quiet -r %d %s %s" % (revision, CLANG_SVN_PATH, clang_dir),
                                     env=my_env, shell=True)
                p.wait()
                if platform.system() == 'Windows':
                    p = subprocess.Popen("svn co --quiet -r %d %s %s" % (revision, LLD_SVN_PATH, lld_dir),
                                         env=my_env, shell=True)
                    p.wait()
                logger.info("Local llvm svn copy revision is set to %d(I)" % revision)
            except Exception, e:
                print "Error while svn co"
                print_error(e)
        else:
            try:
                logger.info("Start updating")
                p = subprocess.Popen("svn cleanup %s" % llvm_dir, env=my_env, shell=True)
                p.wait()
                p = subprocess.Popen("svn cleanup %s" % clang_dir, env=my_env, shell=True)
                p.wait()
                p = subprocess.Popen("svn up --quiet -r %d %s" % (revision, llvm_dir), env=my_env, shell=True)
                p.wait()
                p = subprocess.Popen("svn up --quiet -r %d %s" % (revision, clang_dir), env=my_env, shell=True)
                p.wait()
                if platform.system() == "Windows":
                    p = subprocess.Popen("svn cleanup %s" % lld_dir, env=my_env, shell=True)
                    p.wait()
                    p = subprocess.Popen("svn up --quiet -r %d %s" % (revision, lld_dir), env=my_env, shell=True)
                    p.wait()
                logger.info("Local llvm svn copy revision is set to %d" % revision)
            except Exception, e:
                print "Error while updating svn"
                print_error(e)

    def build_revision(self, revision):
        build_dir = self.BUILD_DIRECTORY + os.path.sep + "build_" + str(revision)
        if os.path.exists(build_dir):
            shutil.rmtree(build_dir, ignore_errors=False, onerror=handle_remove_readonly)
        os.makedirs(build_dir)
        my_env = os.environ.copy()
        if platform.system() == "Windows":
            my_env['PATH'] = my_env['PATH'] + ";" + ATG_WORK_DIR + os.path.sep + "tools" + ";" + "C:\\Program Files\\CMake\\bin"
            os_prep = '"%VS140COMNTOOLS%\\..\\..\\VC\\vcvarsall.bat" amd64 &&'
        else:
            my_env['PATH'] = my_env['PATH'] + ':' + ATG_WORK_DIR + os.path.sep + "tools"
            os_prep = ""
        """Configure"""
        try:
            logger.info("Configuration started")
            FNULL = open(os.devnull, 'w')
            configurator = subprocess.Popen(os_prep + 'cd %s && cmake -G "Ninja" -DLLVM_BINUTILS_INCDIR=/export/users/itaraban/work/atg/binutils-2.29.1/include ..' % build_dir + os.path.sep + 'llvm',
                                            env=my_env, stdout=FNULL, shell=True)
            configurator.wait()
            logger.info("Configuration ended")

            """Ninja build"""
            try:
                logger.info("Building started")
                builder = subprocess.Popen(os_prep + "cd %s && ninja -j%d" % (build_dir, self.threads),
                                           env=my_env, stdout=FNULL, shell=True)
                builder.wait()
                logger.info("Building ended")
                os.rename(build_dir, build_dir + "_DONE")
            except Exception, e:
                print "Error while building"
                print_error(e)
        except Exception, e:
            print "Error while configure"
            print_error(e)

    def get_next_compiler(self):
        if self.compiler_source_type == 'svn':
            try:
                """Check if there is next revision on svn"""
                last_revision = get_last_revision_number()
                if self.compiler_current_version < last_revision:
                    next_revision = last_revision  # self.compiler_current_version + 1, take latest, not increment
                    """Check space and delete tenth old build"""
                    try:
                        if not os.path.exists(self.BUILD_DIRECTORY):
                            os.makedirs(self.BUILD_DIRECTORY)
                        dirs = os.listdir(self.BUILD_DIRECTORY)
                        builds = [x for x in dirs if x.startswith("build_")]
                        if len(builds) > 10:
                            build_names = dict((int(name.split("_")[1]), name) for name in builds)
                            builds_revisions = [int(x.split("_")[1]) for x in builds if x.startswith('build_')]
                            builds_revisions.sort()
                            for old_revision in builds_revisions[:-5]:
                                shutil.rmtree(self.BUILD_DIRECTORY + os.path.sep + build_names[old_revision],
                                              ignore_errors=False, onerror=handle_remove_readonly)
                    except Exception, e:
                        print "Error while working with compiler directory:"
                        print_error(e)
                    self.get_svn_revision(next_revision)
                    self.build_revision(next_revision)
                    self.compiler_current_version = next_revision

            except Exception, e:
                print "Error while connecting with svn"
                print_error(e)
        else:
            """Just check last version on xarch"""
            pass

    @staticmethod
    def retest(compiler, compiler_dir, test_dir, fail_type, opt, last_opt=''):
            if compiler.startswith('clang') and len(last_opt) > 0:
                compiler_source_type = 'svn'
            else:
                compiler_source_type = 'ics'
            test_name = test_dir.split(os.path.sep)[-1]
            if os.path.exists(test_dir + os.path.sep + "input.txt"):
                with_input = True
            else:
                with_input = False
            if os.path.exists(os.path.join(test_dir, test_name + '.c')):
                lang = 'c'
                lib_lang = 'c'
            elif os.path.exists(os.path.join(test_dir, test_name + '.cpp')):
                lang = 'cpp'
                lib_lang = 'cpp'
            elif os.path.exists(os.path.join(test_dir, test_name + '.ll')):
                lang = 'll'
                lib_lang = 'c'
                if not compiler.startswith('clang'):
                    return
            else:
                logger.error("TEST " + test_name + " not found in " + test_dir)
                return
            runner = atg_test.Runner(compiler, compiler_source_type == "svn", "oldgen", test_dir=test_dir)
            try:
                """check build"""
                try:
                    runner.config_compiler()
                except Exception, e:
                    logger.error("error while configure")
                runner.run_input = with_input
                runner.lang = lang
                runner.lib_lang = lib_lang
                """run test"""
                test_result = runner.run_test(test_name=test_name)
                """check test"""
                if test_result == fail_type and opt == runner.opt_last.split(";")[0] and \
                        (len(last_opt) == 0 or last_opt == runner.opt_last.split(";")[1]) and compiler == compiler_dir:
                    # we still have same error
                    # clean directory
                    for file in os.listdir(test_dir):
                        if (file != test_name + "." + lang) and (file != 'input.txt'):
                            os.remove(os.path.join(test_dir, file))
                    return
                # save new invalid test for future
                if test_result == 'invalid':
                    runner.save_test(test_name=test_name)
                if test_result != 'passed' and test_result != 'invalid':
                    if test_result == 'compfail' or test_result == 'runfail':
                        if False: # Disable reduce for retest for some time runner.reduce_test(test_name=test_name):
                            old_opt = runner.opt_last.split(";")[1]
                            retest_result = runner.run_test(test_name="REDUCED-" + test_name)
                            runner.save_test("REDUCED-" + test_name)
                            if retest_result != test_result or old_opt != runner.opt_last.split(";")[1]:
                                runner.save_test(test_name=test_name)
                        else:
                            runner.save_test(test_name=test_name)
                    else:
                        runner.save_test(test_name=test_name)
                #delete test
                if compiler == compiler_dir:
                    for file in os.listdir(test_dir):
                        if (file != test_name + "." + lang) and (file != 'input.txt'):
                            os.remove(os.path.join(test_dir, file))
                    if not os.path.exists(test_dir.replace("fails", "old_fails")):
                        shutil.move(test_dir, test_dir.replace("fails", "old_fails"))
                    else:
                        shutil.rmtree(test_dir, ignore_errors=False, onerror=handle_remove_readonly)
            except Exception, e:
                print_error(e)
                runner.save_test(test_name=test_name)
                time.sleep(60)

    def get_all_fails(self):
        logger.info("Started statistics");
        with open(os.path.join(ATG_HOME_DIR,'fails.csv'), 'wb') as csvfile:
            csv_writer = csv.DictWriter(csvfile, fieldnames=['compiler', 'test', 'path', 'fail', 'opt_level', 'optimization'])
            csv_writer.writeheader()
            if not os.path.exists(os.path.join(ATG_HOME_DIR, "fails")):
                os.path.exists()
            for compiler_dir in os.listdir(os.path.join(ATG_HOME_DIR, "fails")):
                for fail_dir in os.listdir(os.path.join(ATG_HOME_DIR, "fails", compiler_dir)):
                    for opt_dir in os.listdir(os.path.join(ATG_HOME_DIR, "fails", compiler_dir, fail_dir)):
                        opt_path = os.path.join(ATG_HOME_DIR, "fails", compiler_dir, fail_dir, opt_dir)
                        for sub_dir in os.listdir(opt_path):
                            if fail_dir.find("fail") > 0 and not sub_dir.startswith("201"):
                                last_opt_dir = sub_dir
                                for test_dir in os.listdir(os.path.join(opt_path, last_opt_dir)):
                                    csv_writer.writerow({'compiler': compiler_dir,
                                                         'test': test_dir,
                                                         'path': os.path.join(opt_path, last_opt_dir, test_dir),
                                                         'fail': fail_dir,
                                                         'opt_level': opt_dir,
                                                         'optimization': last_opt_dir})
                                if not os.listdir(os.path.join(opt_path, last_opt_dir)):
                                    os.rmdir(os.path.join(opt_path, last_opt_dir))
                            else:
                                csv_writer.writerow({'compiler': compiler_dir,
                                                     'test': sub_dir,
                                                     'path': os.path.join(opt_path, sub_dir),
                                                     'fail': fail_dir,
                                                     'opt_level': opt_dir,
                                                     'optimization': ''})
                        if not os.listdir(opt_path):
                            os.rmdir(opt_path)
                            
        logger.info("Ended");

    def recheck_current_fails(self):
        with open(os.path.join(ATG_HOME_DIR,'fails.csv'), "rb") as csvfile:
            csv_reader = csv.DictReader(csvfile)
            for test in csv_reader:
                compilers = []
                if test['compiler'] == "xmain":
                    compilers.append('clang')
                compilers.append(test['compiler'])
                for compiler in compilers:
                    logger.info("Retesting " + test['fail'] + " at " + test['compiler'] + " with " + compiler + " compiler")
                    self.retest(compiler=compiler,
                                test_dir=test['path'],
                                fail_type=test['fail'], opt=test['opt_level'], last_opt=test['optimization'], compiler_dir=test['compiler'])

def main():
    """parse arguments and options"""
    parser = argparse.ArgumentParser(description='Automatic Test Generator')
    action = parser.add_mutually_exclusive_group(required=True)
    action.add_argument('--build', action='store_true', help='start build process')
    action.add_argument('--retest', action='store_true', help='start retest process')
    
    parser.add_argument('-c', dest='compiler', default='clang', help='type of compiler for ATG. Supported: clang, icx')
    parser.add_argument('-v', dest='version', default='0',
                        help='ATG start position, revision for svn, timestamp for ics')
    parser.add_argument('-j', dest='number_threads', default=4,
                        help='number of threads')
    parser.add_argument('--use-svn', dest='use_svn', action='store_true', help='enable svn usage instead of ics_builds')
    parser.add_argument('--version', action='version', version='%(atg) 0.9')
    args = parser.parse_args()
    atg = ATG(args.compiler, args.use_svn, args.version, args.number_threads, args.build)
    
    while True:
        if args.build:
            atg.get_next_compiler()
        elif args.retest:
            atg.get_all_fails()
            atg.recheck_current_fails()
        # two hours timeout
	
        time.sleep(7200)


if __name__ == "__main__":
    main()
