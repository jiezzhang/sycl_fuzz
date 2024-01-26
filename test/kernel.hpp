#include "libcpp.h"
#include "type_cast.hpp"
#include <CL/sycl.hpp>
using namespace sycl;

struct struct_ksra {
sycl::cl_double v_o;
schar16 v_zc;
sycl::cl_ushort v_iwc;


};

struct struct_xsje {
int v_di;
unsigned int v_qo;
sycl::cl_long4 v_l;


};


float f0_sgw();
int f0_xg();
sycl::cl_half f1_e(double);
sycl::cl_ushort16 f1_dxnxiqhebvlxr(sycl::cl_short8);
unsigned int f1_irb(sycl::cl_double);

void kernel_fun(sycl::queue &queue, sycl::range<1> global_range,
                sycl::range<1> local_range,
                sycl::buffer<ulong, 1> &buf) {
   sycl::cl_char buf_tm_ptr[192] = {30};
   sycl::buffer<sycl::cl_char> buf_tm (buf_tm_ptr, sycl::range(192));

   sycl::cl_char buf_zna_ptr[192] = {42};
   sycl::buffer<sycl::cl_char> buf_zna (buf_zna_ptr, sycl::range(192));


  queue.submit([&](sycl::handler &cgh) {
    auto result = buf.template get_access<sycl::access::mode::read_write>(cgh);
     sycl::accessor <sycl::cl_char, 1, sycl::access::mode::read_write> buf_tm_acc(buf_tm, cgh);
     sycl::accessor <sycl::cl_char, 1, sycl::access::mode::read_write> buf_zna_acc(buf_zna, cgh);



    cgh.parallel_for<class fuzz_kernel>(
      sycl::nd_range<1>(global_range, local_range),
      [=](sycl::nd_item<1> item) {
        sycl::cl_half v_q = sycl::cl_half(16.98);
        unsigned int v_soz = cast<unsigned int>(v_q);

        if (cast<unsigned int>(v_q)) {

          sycl::cl_char4 a1_escg[192] = {sycl::cl_char4(9)};
          ulonglong8 a1_e[192] = {ulonglong8(42)};

          int v_kfc = 1;
          sycl::cl_uchar16 v_yj = sycl::cl_uchar16(16);
          sycl::cl_char v_kdvgtr = 87;

          v_q *= cast<sycl::cl_half>(f0_xg());
          v_kdvgtr++;
          if (cast<short>(v_yj)) {



            v_soz -= f1_irb(cast<sycl::cl_double>(v_kdvgtr));
            for (v_kfc=0; v_kfc <= 57; v_kfc += 3) {

              double a1_nft[192] = {double(64.6)};
              double a1_py[192] = {double(13.89)};

              sycl::cl_ushort16 v_qs = cast<sycl::cl_ushort16>(v_soz);
              sycl::cl_char v_f = 47;
              sycl::cl_half v_sb = sycl::cl_half(76.62);
              sycl::cl_float v_rt = sycl::cl_float(98.9);

              v_kdvgtr -= result[item.get_global_linear_id()];
              a1_e[cast<size_t>(v_kfc)] -= ulonglong8(17);
              if (v_f >= v_kdvgtr) {

                sycl::cl_uchar a1_vhjigac[192] = {19};
                unsigned int a1_olspt[192] = {2};


                result[item.get_global_linear_id()] += f0_xg();
                v_soz *= 70 + v_soz;
                if (result[item.get_global_linear_id()]) {

                  sycl::cl_float a1_r[192] = {sycl::cl_float(45.78)};

                  sycl::cl_half v_l = sycl::cl_half(18.64) + sycl::cl_half(59.31);
                  sycl::cl_half3 v_z = cast<sycl::cl_half3>(v_sb);
                  sycl::cl_char v_fmacfz = 50;

                  v_z += cast<sycl::cl_half3>(v_kfc) - sycl::cl_half3(15);
                  v_qs++;
                  v_yj += (cast<sycl::cl_uchar16>(v_sb));

                }

              } else {

                sycl::cl_half a1_dh[192] = {sycl::cl_half(7.22)};

                int v_kd = 76 + 11;
                int v_rv = cast<int>(v_rt) * 83 + 47;
                half3 v_a = half3(11);
                sycl::cl_ushort8 v_sofhpszf = sycl::cl_ushort8(32) - sycl::cl_ushort8(69) + sycl::cl_ushort8(76);

                v_sb *= cast<sycl::cl_half>(f0_xg());
                if (v_kd) {


                  sycl::cl_double v_lz = sycl::cl_double(96.1) + sycl::cl_double(90.37);

                  if (v_soz) {


                    sycl::cl_char v_rr = 28;
                    sycl::cl_half4 v_og = sycl::cl_half4(37) - sycl::cl_half4(45);
                    sycl::cl_double v_pyxmb = sycl::cl_double(60.29);

                    for (result[item.get_global_linear_id()]=33; result[item.get_global_linear_id()] > v_kfc; result[item.get_global_linear_id()]--) {

                      sycl::cl_half8 a1_tqg[192] = {sycl::cl_half8(97)};
                      float8 a1_j[192] = {float8(95)};

                      int v_l = 78;
                      sycl::cl_ushort v_wrl = v_kdvgtr;
                      sycl::cl_uchar v_w = cast<sycl::cl_uchar>(v_q) + 85;
                      unsigned int v_wyk = v_l;

                      a1_tqg[cast<size_t>(64+2*v_kfc-v_kfc)] -= sycl::cl_half8(95);
                      v_rt *= cast<sycl::cl_float>(f1_e(cast<double>(f1_dxnxiqhebvlxr(sycl::cl_short8(11) - cast<sycl::cl_short8>(f0_xg()) + cast<sycl::cl_short8>(f1_irb(sycl::cl_double(67.74)))))));
                      {


                        sycl::cl_half v_uijod = sycl::cl_half(87.49) + sycl::cl_half(81.59) * sycl::cl_half(37.38);
                        sycl::cl_float v_xm = sycl::cl_float(50.18);
                        float v_eb = float(61.49);
                        sycl::cl_uchar v_tjk = cast<sycl::cl_uchar>(v_pyxmb);

                        ++v_tjk;
                        a1_e[cast<size_t>(96-result[item.get_global_linear_id()])] += cast<ulonglong8>(f1_e(cast<double>(f1_e(double(27.4))))) + copy(cast<ulonglong8>(result[item.get_global_linear_id()]));
                        a1_tqg[cast<size_t>(result[item.get_global_linear_id()]+result[item.get_global_linear_id()])] = cast<sycl::cl_half8>(v_q);

                      }
                      v_wrl = v_w - v_kd - cast<sycl::cl_ushort>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(v_soz))))) - cast<sycl::cl_ushort>(v_pyxmb);

                    }
                    v_rt *= cast<sycl::cl_float>(f1_e(cast<double>(result[item.get_global_linear_id()])));
                    v_f = cast<sycl::cl_char>(f1_dxnxiqhebvlxr(sycl::cl_short8(34)));

                  }
                  v_f *= cast<sycl::cl_char>(f0_sgw());
                  v_sofhpszf *= cast<sycl::cl_ushort8>(f1_e(cast<double>(v_kdvgtr))) * cast<sycl::cl_ushort8>(v_a);

                }
                for (v_soz=3; v_soz <= v_kfc; ++v_soz) {

                  sycl::cl_char a1_x[192] = {54};
                  sycl::cl_uint2 a1_t[192] = {sycl::cl_uint2(8)};

                  float v_nm = float(85.45);
                  float v_hwuccxb = float(32.70);

                  v_a *= half3(97);
                  {

                    sycl::cl_half a1_o[192] = {sycl::cl_half(72.69)};
                    ulonglong2 a1_wqrh[192] = {ulonglong2(25)};

                    sycl::cl_uchar v_z = 75;
                    double16 v_s = double16(57) + double16(66);
                    sycl::cl_char v_w = v_kfc + 21;

                    for (v_kd=v_soz; v_kd <= 63; v_kd += 5) {


                      double v_j = cast<double>(v_a);
                      double v_k = double(46.30) + double(25.61);
                      sycl::cl_short4 v_qk = sycl::cl_short4(17);

                      v_rv = cast<int>(f1_dxnxiqhebvlxr(sycl::cl_short8(63)));
                      ; /* for-cycle skipped due to nesting limit */
                      v_k *= cast<double>(v_a);
                      v_kdvgtr = 8 * v_rv;

                    }
                    for (v_f=0; v_f <= 53; v_f++) {


                      sycl::cl_char v_cy = v_f;
                      long3 v_n = long3(62);
                      sycl::cl_double v_u = sycl::cl_double(56.49);

                      ++v_yj;
                      if (cast<sycl::cl_short>(v_rt)) {

                        unsigned int a1_jxusmuxixc[192] = {97};


                        a1_o[cast<size_t>(3*v_f)] += cast<sycl::cl_half>(v_rv);
                        v_q = cast<sycl::cl_half>(v_kdvgtr);
                        v_n++;

                      }
                      switch (cast<size_t>(cast<int>(f1_e(cast<double>(f0_xg()))) + v_cy)) {
                        case 15:
                          a1_t[cast<size_t>(v_kfc)] += + cast<sycl::cl_uint2>(f0_xg());
                        case 20:
                          v_z += 18;
                          ++v_nm;
                        case 29:
                          ++v_w;
                          buf_zna_acc[cast<size_t>(v_f)] += - 88;

                      }

                    }
                    switch (cast<size_t>(v_rv)) {
                      case 2:
                        v_qs *= sycl::cl_ushort16(27);
                        result[item.get_global_linear_id()] -= 86;
                      case 21:
                        v_rv++;
                      case 92:
                        v_rv = 49 + cast<int>(v_qs);

                      default:
                        a1_e[cast<size_t>(v_kfc)] += ulonglong8(88);
                    }

                  }
                  v_kdvgtr *= 82;

                }
                v_soz -= 98;

              }
              switch (cast<size_t>(9)) {
                case 28:
                  v_q -= cast<sycl::cl_half>(v_sb);
                  break;

                default:
                  buf_zna_acc[cast<size_t>(v_kfc)] = 51;
              }
              for (v_soz=25; v_soz <= 63; ++v_soz) {

                double a1_zn[192] = {double(73.39)};

                sycl::cl_uchar v_t = 63;
                sycl::cl_uchar3 v_j = cast<sycl::cl_uchar3>(v_yj) + sycl::cl_uchar3(47);
                sycl::cl_char v_ve = cast<sycl::cl_char>(v_j);
                sycl::cl_half v_fs = sycl::cl_half(68.9);

                ++v_q;
                a1_escg[cast<size_t>(v_kfc)] -= sycl::cl_char4(55) + cast<sycl::cl_char4>(f1_irb(cast<sycl::cl_double>(v_kfc)));
                v_sb -= cast<sycl::cl_half>(v_sb) + cast<sycl::cl_half>(v_t);
                v_fs = cast<sycl::cl_half>(f0_xg());
                v_rt = sycl::cl_float(81.37) + f0_sgw();

              }
              v_qs -= cast<sycl::cl_ushort16>(f1_e(double(62.92)));


            }
            v_soz += 72;

          } else {

            sycl::cl_double a1_wzy[192] = {sycl::cl_double(19.87)};

            sycl::cl_half2 v_k = cast<sycl::cl_half2>(v_kdvgtr);
            int v_lng = 66;
            sycl::cl_float v_autodknr = cast<sycl::cl_float>(v_k) + sycl::cl_float(93.26);


            ; /* continue statement was omited here */
            {

              sycl::cl_half a1_ze[192] = {sycl::cl_half(2.20)};

              float v_ud = float(77.47);
              unsigned int v_o = 34;
              char16 v_js = cast<char16>(v_yj);
              double v_ppnjivekf = double(77.47) * double(61.83);

              for (v_soz=30; v_soz <= 63; ++v_soz) {

                sycl::cl_half a1_zrp[192] = {sycl::cl_half(80.100)};

                longlong2 v_wr = longlong2(70) - longlong2(24) * longlong2(25);
                unsigned int v_tl = 58 - v_kfc;
                double v_v = double(12.24);

                a1_e[cast<size_t>(160-2*v_soz)] += cast<ulonglong8>(f0_xg());
                a1_e[cast<size_t>(v_soz)] *= ulonglong8(51);
                v_wr = cast<longlong2>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_q)));

              }
              v_lng = 73;
              v_q -= cast<sycl::cl_half>(f1_irb(cast<sycl::cl_double>(v_kfc)));

            }

          }

        } else {

          sycl::cl_half a1_cv[192] = {sycl::cl_half(18.78)};

          longlong16 v_kkszd = longlong16(83);

          v_soz *= result[item.get_global_linear_id()] + 36;
          result[item.get_global_linear_id()] = cast<unsigned long>(f0_sgw());
          for (result[item.get_global_linear_id()]=63; result[item.get_global_linear_id()] > 3; result[item.get_global_linear_id()]--) {

            sycl::cl_ulong a1_tjah[192] = {51};


            v_soz = 76;
            v_kkszd -= longlong16(25) + - longlong16(45);
            buf_zna_acc[cast<size_t>(result[item.get_global_linear_id()])] -= 54 - 75;

          }
          result[item.get_global_linear_id()] *= cast<unsigned long>(v_kkszd);

        }
        for (result[item.get_global_linear_id()]=13; result[item.get_global_linear_id()] <= 63; result[item.get_global_linear_id()]++) {


          ushort2 v_v = ushort2(2);
          sycl::cl_uchar v_d = v_soz;
          sycl::cl_char v_zbhx = 43;
          ulong2 v_mz = ulong2(88) + ulong2(13) + cast<ulong2>(result[item.get_global_linear_id()]);

          v_zbhx *= 69;
          switch (cast<size_t>(result[item.get_global_linear_id()] + f1_irb(sycl::cl_double(71.53)) - - + f0_xg())) {
            case 75:
              v_d++;
              break;
            case 18:
              for (v_d=0; v_d <= 63; ++v_d) {

                sycl::cl_uchar a1_pfxpye[192] = {45};
                double a1_br[192] = {double(47.58)};

                unsigned int v_vn = v_d;

                buf_zna_acc[cast<size_t>(result[item.get_global_linear_id()])] = cast<sycl::cl_char>(v_q);
                v_v *= ushort2(11) * v_v;
                buf_tm_acc[cast<size_t>(64+2*result[item.get_global_linear_id()]-v_d)] -= cast<sycl::cl_char>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_d)));
                v_mz++;

              }
              break;
            case 36:
              v_q = sycl::cl_half(3.63);
              break;

            default:
              break;
              for (v_soz=2; v_soz <= result[item.get_global_linear_id()]; v_soz++) {

                sycl::cl_long a1_wo[192] = {1};
                ushort4 a1_d[192] = {ushort4(9)};

                sycl::cl_char4 v_pkg = cast<sycl::cl_char4>(v_d);
                sycl::cl_uchar v_gvyc = result[item.get_global_linear_id()];
                float v_lkz = cast<float>(v_q);

                if (cast<sycl::cl_short>(v_lkz)) {

                  int a1_j[192] = {64};

                  ulong2 v_iacp = ulong2(20);
                  sycl::cl_char v_r = 27;
                  sycl::cl_uint2 v_c = sycl::cl_uint2(29);
                  float v_ycp = float(40.54);

                  v_c = sycl::cl_uint2(99) + sycl::cl_uint2(96);
                  for (v_gvyc=v_soz; v_gvyc <= 63; ++v_gvyc) {


                    sycl::cl_uint v_qn = 87 + 79;
                    sycl::cl_float4 v_mv = sycl::cl_float4(92);
                    sycl::cl_long4 v_fuwipn = sycl::cl_long4(70);

                    v_mv = cast<sycl::cl_float4>(v_ycp);
                    ; /* for-cycle skipped due to nesting limit */
                    v_r *= v_r;

                  }
                  v_gvyc = cast<sycl::cl_uchar>(f0_sgw());
                  v_gvyc++;
                  v_d = v_r;

                } else {

                  float a1_cv[192] = {float(24.56)};

                  sycl::cl_double v_pa = cast<sycl::cl_double>(v_q);
                  float v_vl = float(93.13) + float(85.3) + cast<float>(v_pkg);
                  sycl::cl_half v_k = sycl::cl_half(77.60);

                  v_v = ushort2(91);
                  v_v = cast<ushort2>(f0_sgw());
                  if (buf_zna_acc[cast<size_t>(result[item.get_global_linear_id()])]) {


                    sycl::cl_uchar v_qm = 43 + 100 - 35;
                    double v_mrxelg = double(12.1);

                    v_q -= sycl::cl_half(82.18) + cast<sycl::cl_half>(a1_wo[cast<size_t>(result[item.get_global_linear_id()])]);
                    v_qm = cast<sycl::cl_uchar>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(a1_d[cast<size_t>(((unsigned int)(67 + 20))%192)]))) - sycl::cl_short8(30) + cast<sycl::cl_short8>(f0_xg())));
                    if (cast<sycl::cl_short>(v_mrxelg)) {


                      sycl::cl_double v_vmp = sycl::cl_double(16.2) - sycl::cl_double(64.57);
                      sycl::cl_long v_u = 17 + cast<sycl::cl_long>(v_vmp);

                      {

                        sycl::cl_char8 a1_pbronsx[192] = {sycl::cl_char8(80)};
                        sycl::cl_ushort2 a1_d[192] = {sycl::cl_ushort2(2)};


                        v_lkz -= cast<float>(buf_tm_acc[cast<size_t>(v_soz)]);
                        a1_d[cast<size_t>(v_soz)] *= cast<ushort4>(buf_zna_acc[cast<size_t>(v_soz)]);
                        if (cast<sycl::cl_long>(v_mz)) {

                          sycl::cl_char a1_raevweksuw[192] = {47};

                          sycl::cl_uchar v_n = 88;
                          ushort2 v_z = ushort2(100);
                          unsigned short v_rcjuatps = 45;
                          sycl::cl_uchar v_yct = 51;


                          ++v_z;
                          v_zbhx = 6;
                          for (v_d=32; v_d <= 63; v_d++) {

                            long8 a1_mggs[192] = {long8(99)};

                            sycl::cl_float v_td = sycl::cl_float(42.68);
                            sycl::cl_char v_emuvm = 59 + v_soz;
                            sycl::cl_float16 v_pgza = sycl::cl_float16(20);
                            uchar2 v_b = uchar2(12);

                            ; /* for-cycle skipped due to nesting limit */
                            v_n++;
                            continue;

                          }

                        }

                      }
                      v_q *= sycl::cl_half(50.21);
                      for (v_u=0; v_u <= result[item.get_global_linear_id()]; ++v_u) {

                        int a1_d[192] = {90};
                        float a1_xqqv[192] = {float(50.61)};


                        ++v_qm;
                        ++v_vl;
                        v_gvyc -= - cast<sycl::cl_uchar>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_q)));

                      }

                    } else {


                      sycl::cl_uchar v_pr = 75 * v_soz;

                      v_mrxelg -= double(96.45);
                      v_qm = cast<sycl::cl_uchar>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f0_xg()) * cast<sycl::cl_short8>(a1_d[cast<size_t>(v_soz)]) - cast<sycl::cl_short8>(v_qm) + + (sycl::cl_short8(52), cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(a1_wo[cast<size_t>(result[item.get_global_linear_id()])]))) - sycl::cl_short8(93) + cast<sycl::cl_short8>(f1_e(double(77.88))))));
                      v_d++;

                    }

                  }

                }
                v_v -= ushort2(81) + cast<ushort2>(buf_tm_acc[cast<size_t>(result[item.get_global_linear_id()])]);
                for (v_gvyc=0; v_gvyc <= 63; v_gvyc++) {

                  sycl::cl_double a1_yetw[192] = {sycl::cl_double(46.50)};

                  uint3 v_st = cast<uint3>(v_soz);
                  sycl::cl_char v_j = 86 + result[item.get_global_linear_id()];
                  float v_pj = float(8.88);

                  v_mz -= ulong2(63) + cast<ulong2>(v_pj);
                  v_j -= f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f0_sgw()))) - cast<sycl::cl_double>(a1_wo[cast<size_t>(v_soz)])) + cast<sycl::cl_char>(f1_e(cast<double>(f0_xg()) - cast<double>(f1_irb(cast<sycl::cl_double>(v_d) + cast<sycl::cl_double>(f1_dxnxiqhebvlxr(sycl::cl_short8(56) + sycl::cl_short8(81)))))));
                  v_v *= ushort2(29);

                }

              }
              v_soz += cast<unsigned int>(v_q);
              v_d++;
              v_soz = cast<unsigned int>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_d)));
              v_d *= 16;
          }
          for (v_q=0; v_q <= 52; ++v_q) {


            float v_fd = float(91.91) + cast<float>(v_q);
            long long v_yvoo = result[item.get_global_linear_id()] + 64;
            unsigned int v_k = 64;
            unsigned int v_itthh = 10;

            buf_zna_acc[cast<size_t>(result[item.get_global_linear_id()])] -= 80;
            for (v_itthh=v_q; v_itthh <= 63; v_itthh++) {

              ulonglong8 a1_f[192] = {ulonglong8(4)};

              sycl::cl_half v_taoq = sycl::cl_half(29.99);
              sycl::cl_short v_iuz = 60;

              ; /* for-cycle skipped due to nesting limit */
              v_d *= result[item.get_global_linear_id()];
              a1_f[cast<size_t>(v_itthh)] += cast<ulonglong8>(f1_e(double(3.14)));

            }
            v_v += cast<ushort2>(f1_e(cast<double>(v_q) - double(100.41) * cast<double>(f1_dxnxiqhebvlxr(sycl::cl_short8(88) + sycl::cl_short8(43) + cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_e(double(54.5))))))) + double(86.37) + cast<double>(f1_e(cast<double>(v_q)))));

          }

        }
        v_soz = 74;
    });
  });
}
float f0_sgw() {

  int a1_z[192] = {22};


  ; /* lvalue change could be here */
  {

    sycl::cl_half a1_nkaxg[192] = {sycl::cl_half(29.22)};
    double a1_b[192] = {double(86.76)};

    sycl::cl_char v_yru = 50 + 78;
    float v_p = float(80.98);
    double v_ntxjsijdbnqcp = double(14.64);

    ++v_yru;
    {


      long v_f = 36;

      switch (cast<size_t>(v_f)) {
        case 92:
          for (v_p=5; v_p <= 63; v_p++) {

            char2 a1_krms[192] = {char2(84)};
            double a1_rzg[192] = {double(29.93)};

            double v_zkdakeaurtdffqv = double(19.61);
            sycl::cl_int v_c = cast<sycl::cl_int>(v_zkdakeaurtdffqv);
            sycl::cl_uchar v_lpvhd = 2;

            v_c += 1;
            for (v_lpvhd=0; v_lpvhd <= 51; ++v_lpvhd) {


              sycl::cl_int8 v_ie = sycl::cl_int8(13);
              double v_armaxenuqnmkvpqn = double(46.63);
              sycl::cl_double3 v_yfl = sycl::cl_double3(66);
              unsigned long v_y = cast<unsigned long>(v_yfl);

              v_ntxjsijdbnqcp += cast<double>(v_yru);
              v_ie *= cast<sycl::cl_int8>(v_yfl);
              for (v_zkdakeaurtdffqv=v_p; v_zkdakeaurtdffqv <= v_p; ++v_zkdakeaurtdffqv) {

                ushort4 a1_y[192] = {ushort4(5)};
                ushort2 a1_p[192] = {ushort2(27)};

                sycl::cl_float v_wbgybacsfly = v_armaxenuqnmkvpqn + sycl::cl_float(5.41);

                v_yfl = sycl::cl_double3(31) - cast<sycl::cl_double3>(v_p);
                v_yru++;
                v_armaxenuqnmkvpqn = cast<double>(f0_xg());
                {

                  sycl::cl_float a1_jqj[192] = {sycl::cl_float(69.29)};

                  schar4 v_s = + schar4(13);
                  sycl::cl_char v_bg = cast<sycl::cl_char>(v_zkdakeaurtdffqv) + 10 + cast<sycl::cl_char>(v_ntxjsijdbnqcp);
                  sycl::cl_half v_hqcyua = sycl::cl_half(88.66);

                  v_ie = cast<sycl::cl_int8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(a1_p[cast<size_t>(v_zkdakeaurtdffqv)]))) + sycl::cl_short8(94)));
                  ; /* for-cycle skipped due to nesting limit */
                  if (cast<unsigned long>(v_armaxenuqnmkvpqn)) {


                    sycl::cl_uchar v_tlvz = 40;

                    ; /* for-cycle skipped due to nesting limit */
                    ; /* for-cycle skipped due to nesting limit */
                    {

                      sycl::cl_half a1_unx[192] = {sycl::cl_half(78.88)};
                      sycl::cl_long3 a1_i[192] = {sycl::cl_long3(100)};

                      char16 v_kx = cast<char16>(v_s);
                      sycl::cl_ulong4 v_intmh = sycl::cl_ulong4(26);
                      double v_mzm = v_wbgybacsfly;
                      sycl::cl_float v_a = sycl::cl_float(48.20);

                      v_wbgybacsfly = cast<sycl::cl_float>(f1_irb(sycl::cl_double(98.36)));
                      ; /* for-cycle skipped due to nesting limit */
                      v_kx = cast<char16>(f0_xg()) + char16(75);
                      v_a -= (sycl::cl_float(68.62));
                      v_hqcyua += cast<sycl::cl_half>(f1_e(cast<double>(a1_i[cast<size_t>(v_zkdakeaurtdffqv)])));
                      ; /* for-cycle skipped due to nesting limit */
                      return float(23.1) * cast<float>(a1_unx[cast<size_t>(v_zkdakeaurtdffqv)]) + cast<float>(v_c);
                    }
                    return cast<float>(f0_xg());
                  } else {

                    sycl::cl_int2 a1_xu[192] = {sycl::cl_int2(39)};
                    short2 a1_jig[192] = {short2(5)};

                    longlong16 v_nckxphxnyvp = cast<longlong16>(v_armaxenuqnmkvpqn) * cast<longlong16>(v_lpvhd);

                    {


                      double v_k = v_zkdakeaurtdffqv;

                      ++v_c;
                      ; /* for-cycle skipped due to nesting limit */
                      v_bg *= cast<sycl::cl_char>(v_p) * cast<sycl::cl_char>(v_p);
                      return v_armaxenuqnmkvpqn;
                    }
                    v_ie -= + cast<sycl::cl_int8>(f0_xg());
                    v_armaxenuqnmkvpqn = double(7.78);
                    return cast<float>(f1_irb(cast<sycl::cl_double>(f1_e(cast<double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_e(cast<double>(v_bg)))))))));
                  }
                  return cast<float>(f0_xg());
                }
                return float(90.91);
              }
              return cast<float>(f1_e(cast<double>(v_c)));
            }
            for (v_f=63; v_f > v_p; --v_f) {


              sycl::cl_ushort3 v_sq = sycl::cl_ushort3(33);

              ++v_ntxjsijdbnqcp;
              v_lpvhd -= 86;
              v_c = 71;
              return cast<float>(v_lpvhd);
            }
            for (v_c=0; v_c <= 63; v_c++) {



              v_f -= 6;
              for (v_yru=0; v_yru <= 63; v_yru++) {


                int8 v_o = int8(83);
                int v_yuvqip = cast<int>(v_zkdakeaurtdffqv);
                sycl::cl_double v_b = sycl::cl_double(49.52) + sycl::cl_double(96.47);
                sycl::cl_float v_y = sycl::cl_float(22.39);

                v_zkdakeaurtdffqv -= cast<double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(15.55)))));
                v_ntxjsijdbnqcp += cast<double>(f1_irb(cast<sycl::cl_double>(v_yuvqip)));
                v_y *= cast<sycl::cl_float>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_e(double(64.37) - cast<double>(v_o))))))) + sycl::cl_float(4.67);
                return cast<float>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_e(a1_rzg[cast<size_t>(v_p)] + cast<double>(f1_irb(cast<sycl::cl_double>(f0_xg()))))) * cast<sycl::cl_short8>(f1_e(v_ntxjsijdbnqcp * double(79.55) * v_ntxjsijdbnqcp + v_ntxjsijdbnqcp))));
              }
              for (v_yru=v_p; v_yru <= 63; v_yru++) {



                v_ntxjsijdbnqcp += cast<double>(a1_krms[cast<size_t>(v_yru)]);
                v_ntxjsijdbnqcp += cast<double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(sycl::cl_short8(46)))));
                v_ntxjsijdbnqcp = cast<double>(f1_irb(sycl::cl_double(3.79)));
                return cast<float>(v_c) + v_ntxjsijdbnqcp;
              }
              return cast<float>(v_yru);
            }
            v_lpvhd = cast<sycl::cl_uchar>(a1_rzg[cast<size_t>(v_p)]);
            return float(10.65) * float(84.96);
          }
          v_ntxjsijdbnqcp -= double(47.50);
          break;
        case 44:
          for (v_yru=17; v_yru <= 38; ++v_yru) {

            float a1_t[192] = {float(88.99)};
            sycl::cl_half a1_l[192] = {sycl::cl_half(33.80)};

            longlong4 v_qm = + longlong4(7);

            v_ntxjsijdbnqcp = cast<double>(f1_irb(sycl::cl_double(33.23)));
            v_f *= f1_irb(cast<sycl::cl_double>(v_qm));
            if ((v_yru)) {



              v_qm *= cast<longlong4>(v_ntxjsijdbnqcp) + cast<longlong4>(f0_xg());
              v_qm += cast<longlong4>(f0_xg());
              switch (cast<size_t>(cast<int>(v_ntxjsijdbnqcp))) {
                case 33:
                  v_qm -= cast<longlong4>(v_f);
                case 86:
                  v_ntxjsijdbnqcp *= cast<double>(v_yru) + double(86.63);
                  break;
                case 65:
                  v_qm = cast<longlong4>(v_f);
                  break;

                default:
                  v_ntxjsijdbnqcp *= double(78.32);
                  v_ntxjsijdbnqcp -= double(72.91) * cast<double>(v_yru);
                  v_qm -= v_qm;
              }
              return cast<float>(v_yru);
            }
            return v_p;
          }
        case 55:
          v_f = 92;
          v_ntxjsijdbnqcp *= double(87.30);
          break;

      }
      switch (cast<size_t>(cast<int>(f1_e(cast<double>(v_yru) + double(7.15))) * cast<int>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_ntxjsijdbnqcp))))) {
        case 95:
          for (v_ntxjsijdbnqcp=63; v_ntxjsijdbnqcp > 10; --v_ntxjsijdbnqcp) {

            float a1_q[192] = {float(24.18)};
            int a1_mthoni[192] = {12};

            float v_pwd = float(86.8);
            sycl::cl_double v_mfdxe = v_ntxjsijdbnqcp + sycl::cl_double(19.12);
            sycl::cl_double v_hwb = sycl::cl_double(27.96);

            v_pwd *= cast<float>(f1_e(cast<double>(f0_xg())));
            for (v_pwd=0; v_pwd <= 39; ++v_pwd) {

              float a1_zukmzr[192] = {float(71.1)};
              sycl::cl_uchar a1_jqxk[192] = {68};

              sycl::cl_half v_kwckdpgpunt = cast<sycl::cl_half>(v_hwb);
              sycl::cl_short4 v_vwulw = sycl::cl_short4(20) * cast<sycl::cl_short4>(v_kwckdpgpunt);
              sycl::cl_half v_uwk = cast<sycl::cl_half>(v_vwulw) + sycl::cl_half(61.28) + sycl::cl_half(34.11) + sycl::cl_half(65.11);

              v_yru += 82 + cast<sycl::cl_char>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_hwb))) + (26);
              v_p = float(66.100) * v_hwb;
              for (v_mfdxe=v_pwd; v_mfdxe > v_pwd; v_mfdxe--) {


                sycl::cl_char v_blmasqrvj = 21;
                sycl::cl_half4 v_g = sycl::cl_half4(66) - cast<sycl::cl_half4>(v_pwd) - sycl::cl_half4(74);
                sycl::cl_half v_jy = sycl::cl_half(5.66);
                sycl::cl_short v_gb = 83 + 59;

                ; /* for-cycle skipped due to nesting limit */
                ; /* for-cycle skipped due to nesting limit */
                ; /* for-cycle skipped due to nesting limit */
                return cast<float>(f1_e(v_ntxjsijdbnqcp));
              }
              v_uwk -= cast<sycl::cl_half>(v_pwd) + sycl::cl_half(73.9);
              return cast<float>(f1_e(cast<double>(v_yru)));
            }
            v_mfdxe++;
            return float(12.33);
          }
          v_f = f1_irb(sycl::cl_double(4.20));

      }
      v_p = cast<float>(f1_e(v_p)) + cast<float>(f1_irb(sycl::cl_double(16.35)));
      return float(53.100);
    }
    ++v_ntxjsijdbnqcp;
    return cast<float>(f1_e(double(76.60))) - float(85.22) + float(4.56);
  }
  ; /* for-cycle skipped due to no free lvals variables */
  return float(44.26);
}
int f0_xg() {

  sycl::cl_char a1_rpt[192] = {59};
  sycl::cl_double a1_g[192] = {sycl::cl_double(30.78)};

  sycl::cl_uchar v_jna = 51;
  sycl::cl_half v_mdju = sycl::cl_half(38.99);
  unsigned int v_awe = 10;
  int8 v_z = int8(88);

  v_mdju = sycl::cl_half(88.98);
  v_mdju = cast<sycl::cl_half>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(sycl::cl_double(19.25))) + cast<sycl::cl_short8>(f1_e(double(20.28)))));
  v_jna -= f1_irb(sycl::cl_double(43.28));
  return cast<int>(f1_dxnxiqhebvlxr(copy(cast<sycl::cl_short8>(v_mdju))));
}
sycl::cl_half f1_e(double arg_1) {

  long long a1_ndb[192] = {82};
  float a1_wh[192] = {float(78.39)};

  sycl::cl_uint8 v_uepcf = cast<sycl::cl_uint8>(arg_1);
  double v_wagx = arg_1 * double(31.12);
  unsigned int v_e = cast<unsigned int>(v_wagx);
  double v_b = double(46.47) + double(78.30);

  v_wagx += v_wagx;
  switch (cast<size_t>(f1_irb(sycl::cl_double(50.26)))) {
    case 85:
      arg_1 = arg_1;
    case 65:
      v_wagx -= double(46.13);
      if (f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(sycl::cl_short8(83)))))))))))) <= cast<long long>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_wagx)))) {


        ushort4 v_d = + cast<ushort4>(v_wagx) + cast<ushort4>(v_uepcf);
        sycl::cl_half v_qn = sycl::cl_half(52.12);
        sycl::cl_short3 v_zaxn = sycl::cl_short3(37);
        char4 v_gq = char4(92);

        if (cast<sycl::cl_long>(v_b)) {

          sycl::cl_double a1_owxo[192] = {sycl::cl_double(39.7)};
          unsigned short a1_z[192] = {33};

          sycl::cl_double2 v_bjufydn = sycl::cl_double2(33);
          sycl::cl_double v_dzruhox = cast<sycl::cl_double>(v_gq);
          sycl::cl_short2 v_vy = - cast<sycl::cl_short2>(v_wagx);
          sycl::cl_char v_zj = 87 * 88;

          v_wagx -= double(99.26);
          v_zj++;
          v_bjufydn = sycl::cl_double2(20);
          ++v_dzruhox;
          return cast<sycl::cl_half>(v_zj);
        }
        v_d = ushort4(2);
        v_d = ushort4(32);
        return cast<sycl::cl_half>(f1_irb(cast<sycl::cl_double>(v_zaxn) + v_wagx - cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(arg_1))) * cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_qn) + sycl::cl_short8(55))))) * sycl::cl_double(99.80))) - sycl::cl_half(5.60) + cast<sycl::cl_half>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(v_qn) + cast<sycl::cl_double>(f1_dxnxiqhebvlxr(sycl::cl_short8(37))) - cast<sycl::cl_double>(v_gq) * v_b)) + cast<sycl::cl_short8>(f1_irb(sycl::cl_double(17.83)))));
      } else {

        sycl::cl_uchar a1_g[192] = {18};

        int v_imjdekb = 57 + 37 + 99;
        unsigned long long v_x = + v_imjdekb + 78;

        v_imjdekb += v_x;
        v_uepcf = cast<sycl::cl_uint8>(f1_dxnxiqhebvlxr(sycl::cl_short8(56)));
        v_uepcf += cast<sycl::cl_uint8>(f1_irb(cast<sycl::cl_double>(v_uepcf))) - cast<sycl::cl_uint8>(v_e) + cast<sycl::cl_uint8>(f1_dxnxiqhebvlxr(sycl::cl_short8(97)));
        return cast<sycl::cl_half>(v_b);
      }
      for (v_wagx=25; v_wagx <= 33; ++v_wagx) {

        sycl::cl_float a1_umqq[192] = {sycl::cl_float(93.93)};
        sycl::cl_half a1_dh[192] = {sycl::cl_half(73.47)};


        v_e *= f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(sycl::cl_short8(45)))))))) + f1_irb(cast<sycl::cl_double>(a1_ndb[cast<size_t>(3*v_wagx)]) + cast<sycl::cl_double>(f1_irb(v_wagx)));
        for (v_b=21; v_b <= 40; v_b++) {

          sycl::cl_double3 a1_wyckhjb[192] = {sycl::cl_double3(34)};
          sycl::cl_half a1_aolos[192] = {sycl::cl_half(52.29)};

          int v_pqbl = 4 + 74 + cast<int>(v_b);
          sycl::cl_double v_cc = sycl::cl_double(65.67);

          v_pqbl -= cast<int>(f1_dxnxiqhebvlxr(- cast<sycl::cl_short8>(v_e)));
          v_pqbl -= cast<int>(v_b);
          v_uepcf++;
          v_e = 82;
          return cast<sycl::cl_half>(f1_dxnxiqhebvlxr(sycl::cl_short8(99) + (sycl::cl_short8(97), cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(+ cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(sycl::cl_short8(48))))))))));
        }
        for (v_b=22; v_b <= v_wagx; ++v_b) {

          float a1_r[192] = {float(59.71)};
          sycl::cl_short a1_ipbvfaa[192] = {20};

          half4 v_mm = half4(24);
          float v_z = float(97.27) + cast<float>(v_e);
          sycl::cl_char v_d = 20 * 13 * 52;

          v_d *= f1_irb(sycl::cl_double(98.37)) - cast<sycl::cl_char>(v_z);
          arg_1 = cast<double>(f1_irb(sycl::cl_double(62.88))) * cast<double>(f1_dxnxiqhebvlxr(sycl::cl_short8(96) + cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(v_d)))));
          v_uepcf -= cast<sycl::cl_uint8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(a1_dh[cast<size_t>(2*v_b)])));
          return sycl::cl_half(41.18);
        }
        arg_1 += cast<double>(v_e);
        v_b = double(3.47) * v_b;
        return cast<sycl::cl_half>(v_b) - cast<sycl::cl_half>(v_e);
      }

    default:
      v_b += arg_1;
  }
  v_e++;
  {

    sycl::cl_char a1_zub[192] = {23};

    sycl::cl_uchar v_o = cast<sycl::cl_uchar>(v_b);

    for (v_wagx=0; v_wagx <= 63; v_wagx++) {


      int v_f = cast<int>(arg_1);

      ++v_f;
      for (arg_1=2; arg_1 <= v_wagx; arg_1 += 1) {


        sycl::cl_char2 v_lqhof = sycl::cl_char2(67);
        sycl::cl_half v_t = sycl::cl_half(96.81) + sycl::cl_half(41.46) - cast<sycl::cl_half>(v_f);

        v_t = cast<sycl::cl_half>(f1_irb(sycl::cl_double(5.77) + sycl::cl_double(57.57)));
        v_b = double(91.87) + double(16.70);
        ++v_t;
        return cast<sycl::cl_half>(v_t);
      }
      for (v_b=0; v_b <= 60; v_b++) {

        int a1_afmq[192] = {83};
        sycl::cl_float a1_ikr[192] = {sycl::cl_float(27.88)};

        sycl::cl_int16 v_hlw = cast<sycl::cl_int16>(v_e);
        sycl::cl_half v_cakhxo = sycl::cl_half(82.26);
        int4 v_hscat = int4(23);
        int v_q = v_e;

        v_o -= v_o;
        v_uepcf = cast<sycl::cl_uint8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(a1_wh[cast<size_t>(v_wagx)]))))) * cast<sycl::cl_short8>(f1_irb(sycl::cl_double(85.75))) - cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(copy(cast<sycl::cl_short8>(v_b))))));
        if (v_e) {

          sycl::cl_float8 a1_g[192] = {sycl::cl_float8(91)};
          sycl::cl_double3 a1_h[192] = {sycl::cl_double3(85)};


          for (v_e=v_wagx; v_e <= v_b; v_e++) {



            v_cakhxo += sycl::cl_half(5.27) + cast<sycl::cl_half>(v_hlw);
            {


              sycl::cl_char v_muwa = 16;
              sycl::cl_uchar v_cov = 51;
              sycl::cl_half v_cdko = cast<sycl::cl_half>(v_b);
              sycl::cl_ulong2 v_zwwwqrk = sycl::cl_ulong2(71) + cast<sycl::cl_ulong2>(v_q);

              v_hscat = cast<int4>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(copy(v_b))) + cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_cov)))))))));
              {


                double v_jw = double(51.78) - double(30.96);
                char2 v_n = char2(59);
                sycl::cl_uchar v_h = 99;

                v_zwwwqrk += cast<sycl::cl_ulong2>(f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_jw))) + sycl::cl_double(46.78) + cast<sycl::cl_double>(f1_irb(sycl::cl_double(53.60))))))))) * cast<sycl::cl_short8>(v_cakhxo)))));
                v_jw *= cast<double>(v_o) - cast<double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(sycl::cl_double(31.95))) + sycl::cl_short8(78))) + cast<double>(f1_irb(sycl::cl_double(36.95) - sycl::cl_double(5.39)));
                v_uepcf += cast<sycl::cl_uint8>(f1_dxnxiqhebvlxr(sycl::cl_short8(88)));
                v_cov = 39;
                return cast<sycl::cl_half>(a1_ikr[cast<size_t>(v_wagx)]);
              }
              arg_1 = double(13.69);
              return sycl::cl_half(71.75);
            }
            ; /* for-cycle skipped due to nesting limit */
            ++arg_1;
            return cast<sycl::cl_half>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_o)));
          }
          for (v_e=v_b; v_e <= v_b; ++v_e) {

            sycl::cl_float a1_y[192] = {sycl::cl_float(37.51)};
            sycl::cl_uchar8 a1_wzhdwoqbd[192] = {sycl::cl_uchar8(38)};

            sycl::cl_uchar v_jvlkt = v_q;
            sycl::cl_long v_l = 21;

            ; /* for-cycle skipped due to nesting limit */
            ; /* for-cycle skipped due to nesting limit */
            v_f = cast<int>(v_wagx);
            return cast<sycl::cl_half>(f1_dxnxiqhebvlxr(sycl::cl_short8(67)));
          }
          v_hlw = sycl::cl_int16(76);
          v_q *= f1_irb(sycl::cl_double(36.62));
          return cast<sycl::cl_half>(v_hscat);
        } else {

          unsigned int a1_g[192] = {89};

          sycl::cl_ushort16 v_h = sycl::cl_ushort16(23);

          v_q += f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr((sycl::cl_short8(13)))))));
          if (cast<sycl::cl_char>(v_cakhxo)) {

            sycl::cl_double a1_jm[192] = {sycl::cl_double(63.77)};

            sycl::cl_half v_sjbun = sycl::cl_half(16.6);
            sycl::cl_double v_v = cast<sycl::cl_double>(v_sjbun);
            sycl::cl_uchar v_lpcr = cast<sycl::cl_uchar>(v_b);

            for (v_f=0; v_f <= 63; ++v_f) {



              {

                sycl::cl_uchar a1_sky[192] = {58};

                sycl::cl_char v_js = 8;

                v_h *= cast<sycl::cl_ushort16>(v_cakhxo);
                ++v_uepcf;
                v_lpcr = - f1_irb(cast<sycl::cl_double>(f1_irb(v_wagx)));
                v_q = cast<int>(arg_1);
                v_hlw -= - cast<sycl::cl_int16>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(sycl::cl_short8(64))) + cast<sycl::cl_short8>(v_v)));
                v_hlw -= cast<sycl::cl_int16>(f1_irb(cast<sycl::cl_double>(f1_irb(v_v - sycl::cl_double(2.20)))));
                ; /* for-cycle skipped due to nesting limit */
                return cast<sycl::cl_half>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(sycl::cl_short8(30)))));
              }
              v_o -= f1_irb(sycl::cl_double(85.10));
              v_hscat = cast<int4>(f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_cakhxo)))))));
              return cast<sycl::cl_half>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_e)))));
            }
            v_e = 59;
            {

              sycl::cl_int3 a1_b[192] = {sycl::cl_int3(5)};
              sycl::cl_double a1_i[192] = {sycl::cl_double(87.52)};

              sycl::cl_char8 v_gab = sycl::cl_char8(76) + sycl::cl_char8(3);
              sycl::cl_double v_uodv = cast<sycl::cl_double>(v_sjbun) + cast<sycl::cl_double>(v_hlw);

              v_q -= cast<int>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(sycl::cl_short8(93)))));
              v_q = cast<int>(arg_1);
              if (cast<sycl::cl_ulong>(v_v)) {


                char3 v_vsjxx = char3(59);

                v_vsjxx *= cast<char3>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(95.61) + sycl::cl_double(41.25))) + sycl::cl_double(67.99) - cast<sycl::cl_double>(f1_irb(v_uodv))));
                v_uodv = cast<sycl::cl_double>(a1_g[cast<size_t>(2*v_b)]) * cast<sycl::cl_double>(f1_irb(arg_1 + sycl::cl_double(80.3) * sycl::cl_double(42.94)));
                v_hscat *= int4(70);
                return cast<sycl::cl_half>(v_cakhxo);
              }
              return cast<sycl::cl_half>(v_sjbun);
            }
            return cast<sycl::cl_half>(f1_dxnxiqhebvlxr(sycl::cl_short8(49))) * cast<sycl::cl_half>(f1_irb(v_v));
          } else {

            unsigned int a1_chxrw[192] = {70};
            long3 a1_e[192] = {long3(56)};

            ushort3 v_d = ushort3(100);
            float v_lu = v_b;

            {

              int a1_a[192] = {65};

              sycl::cl_uchar v_s = 52;

              ++v_q;
              for (v_f=3; v_f <= 41; v_f++) {

                float3 a1_kxs[192] = {float3(59)};
                double2 a1_osvqdodddtxuu[192] = {double2(35)};

                sycl::cl_int16 v_ype = sycl::cl_int16(72);
                sycl::cl_uint v_rf = 93;
                sycl::cl_char v_nlu = v_q + 45;
                long3 v_zyw = long3(83) * long3(49) * cast<long3>(v_s);

                v_lu = cast<float>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(sycl::cl_short8(82) * cast<sycl::cl_short8>(v_s))) + cast<sycl::cl_short8>(v_rf))) * cast<float>(a1_afmq[cast<size_t>(180-2*v_f)]);
                v_s -= cast<sycl::cl_uchar>(arg_1) + cast<sycl::cl_uchar>(arg_1);
                switch (cast<size_t>(v_e)) {
                  case 17:
                    switch (cast<size_t>(v_nlu + cast<int>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(sycl::cl_double(15.77) + cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(37.6))) + cast<sycl::cl_double>(v_e) - cast<sycl::cl_double>(f1_dxnxiqhebvlxr(sycl::cl_short8(14) * sycl::cl_short8(43) * cast<sycl::cl_short8>(f1_irb(sycl::cl_double(78.65))))))) + v_b)) + sycl::cl_short8(72))))) {
                      case 57:
                        v_cakhxo = sycl::cl_half(60.48);
                        break;

                    }
                  case 15:
                    v_uepcf += cast<sycl::cl_uint8>(v_d);
                  case 30:
                    v_d *= cast<ushort3>(v_zyw);
                    break;
                  case 24:
                    if (v_q) {



                      v_hscat *= int4(83) + int4(22) * int4(59);
                      v_zyw -= long3(85);
                      v_s *= cast<sycl::cl_uchar>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_nlu))) + sycl::cl_double(92.45)))));
                      v_e *= 85;
                      return cast<sycl::cl_half>(v_lu);
                    } else {


                      sycl::cl_uchar v_au = 35;
                      sycl::cl_half v_v = sycl::cl_half(12.90);
                      sycl::cl_float3 v_yr = sycl::cl_float3(72);

                      v_ype = sycl::cl_int16(22);
                      v_s = 86;
                      arg_1 = double(41.95);
                      if (cast<sycl::cl_int>(v_d)) {

                        sycl::cl_float a1_qxg[192] = {sycl::cl_float(15.95)};

                        double2 v_p = double2(28);
                        double v_ino = double(87.35);
                        sycl::cl_char v_t = 10;

                        ; /* for-cycle skipped due to nesting limit */
                        v_hscat -= cast<int4>(v_q) * cast<int4>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_au) * copy(cast<sycl::cl_short8>(v_q))));
                        {

                          unsigned int a1_fb[192] = {67};
                          short4 a1_ou[192] = {short4(59)};


                          ; /* for-cycle skipped due to nesting limit */
                          v_rf = v_au;
                          v_ype++;
                          ; /* for-cycle skipped due to nesting limit */
                          return cast<sycl::cl_half>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(88.94))))))) * sycl::cl_half(47.12);
                        }
                        return sycl::cl_half(14.43) + cast<sycl::cl_half>(f1_irb(sycl::cl_double(50.100)));
                      }
                      v_v -= cast<sycl::cl_half>(v_v);
                      switch (cast<size_t>(v_s)) {
                        case 44:
                          ; /* for-cycle skipped due to nesting limit */
                          break;
                        case 65:
                          v_q += (91 + 24 * cast<int>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_v) + (cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_lu)))))) * 83 + cast<int>(f1_dxnxiqhebvlxr(sycl::cl_short8(39))));

                      }
                      ; /* for-cycle skipped due to nesting limit */
                      return cast<sycl::cl_half>(v_au) * cast<sycl::cl_half>(f1_dxnxiqhebvlxr(sycl::cl_short8(36)));
                    }
                    break;

                }
                return cast<sycl::cl_half>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(sycl::cl_double(40.64))))) + cast<sycl::cl_half>(f1_irb(sycl::cl_double(80.44)));
              }
              v_h -= sycl::cl_ushort16(20);
              return sycl::cl_half(14.86);
            }
            arg_1 = v_wagx;
            v_e -= cast<unsigned int>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(sycl::cl_short8(93) - sycl::cl_short8(30) - sycl::cl_short8(74))))) + cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(sycl::cl_short8(79) * cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(a1_afmq[cast<size_t>(v_wagx)]))))))) * f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(34.32))))));
            return (sycl::cl_half(43.20), cast<sycl::cl_half>(a1_ndb[cast<size_t>(v_b)])) * cast<sycl::cl_half>(f1_irb(v_lu)) + cast<sycl::cl_half>(f1_dxnxiqhebvlxr(sycl::cl_short8(77)));
          }
          v_f = 39;
          return sycl::cl_half(6.89) - cast<sycl::cl_half>(v_e);
        }
        return cast<sycl::cl_half>(v_e);
      }
      if (cast<long>(v_wagx)) {

        sycl::cl_double a1_xlu[192] = {sycl::cl_double(72.50)};

        uchar4 v_dkzirqrtwk = cast<uchar4>(v_e);

        for (v_b=32; v_b <= v_wagx; ++v_b) {

          sycl::cl_half a1_z[192] = {sycl::cl_half(13.50)};
          sycl::cl_float a1_uge[192] = {sycl::cl_float(86.25)};

          sycl::cl_ulong2 v_xd = sycl::cl_ulong2(76) + sycl::cl_ulong2(68) + sycl::cl_ulong2(79);

          v_uepcf = cast<sycl::cl_uint8>(f1_dxnxiqhebvlxr(sycl::cl_short8(67)));
          for (v_o=v_wagx; v_o <= v_b; ++v_o) {


            sycl::cl_uchar v_no = cast<sycl::cl_uchar>(v_xd);
            sycl::cl_half v_g = cast<sycl::cl_half>(v_b);
            sycl::cl_char v_y = 8;

            switch (cast<size_t>(f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(sycl::cl_short8(73) + cast<sycl::cl_short8>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(a1_wh[cast<size_t>(3*v_b)])))))))) {
              case 67:
                ; /* for-cycle skipped due to nesting limit */

            }
            v_no *= v_no;
            ++v_no;
            return cast<sycl::cl_half>(a1_zub[cast<size_t>(v_wagx)]);
          }
          if ((v_e)) {

            float a1_aw[192] = {float(95.78)};
            unsigned short a1_td[192] = {62};


            arg_1 = cast<double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(v_f) + sycl::cl_short8(52)));
            v_o++;
            for (v_o=v_wagx; v_o <= 60; v_o++) {


              sycl::cl_int4 v_buuer = sycl::cl_int4(74);
              sycl::cl_long4 v_wxtv = sycl::cl_long4(32);

              {

                long16 a1_pu[192] = {long16(70)};
                uchar4 a1_w[192] = {uchar4(91)};

                sycl::cl_float v_s = sycl::cl_float(36.73);
                sycl::cl_uchar v_a = 57 + cast<sycl::cl_uchar>(v_s) + 62;
                int3 v_ylc = int3(71);
                sycl::cl_short3 v_xmkdemwodpzh = sycl::cl_short3(90) + cast<sycl::cl_short3>(v_b) - sycl::cl_short3(5);

                v_e = f1_irb(cast<sycl::cl_double>(f1_dxnxiqhebvlxr(sycl::cl_short8(92) * cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(a1_z[cast<size_t>(v_b)]))))));
                v_f += 66;
                ; /* for-cycle skipped due to nesting limit */
                return cast<sycl::cl_half>(f1_irb(sycl::cl_double(92.67)));
              }
              v_buuer *= sycl::cl_int4(73) - sycl::cl_int4(81);
              switch (cast<size_t>(cast<int>(a1_z[cast<size_t>(64+2*v_wagx-v_o)]) * 1)) {
                case 14:
                  ; /* for-cycle skipped due to nesting limit */
                  v_buuer += cast<sycl::cl_int4>(f1_dxnxiqhebvlxr(sycl::cl_short8(85)));
                  v_dkzirqrtwk += cast<uchar4>(v_o);

              }
              return cast<sycl::cl_half>(f1_dxnxiqhebvlxr(sycl::cl_short8(55) + (- cast<sycl::cl_short8>(f1_irb(v_b))) + sycl::cl_short8(57)));
            }
            return sycl::cl_half(6.89) + cast<sycl::cl_half>(v_uepcf);
          }
          arg_1 += cast<double>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(v_e) * cast<sycl::cl_double>(v_o))))) + cast<double>(a1_zub[cast<size_t>(v_wagx)]);
          arg_1++;
          return cast<sycl::cl_half>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(99.89))))))) + cast<sycl::cl_half>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(arg_1) * cast<sycl::cl_short8>(v_o) + cast<sycl::cl_short8>(v_dkzirqrtwk) + cast<sycl::cl_short8>(v_o)));
        }
        v_o++;
        v_uepcf = cast<sycl::cl_uint8>(a1_ndb[cast<size_t>(v_wagx)]);
        return sycl::cl_half(15.22);
      }
      ++v_uepcf;
      return cast<sycl::cl_half>(f1_irb(sycl::cl_double(57.25)));
      return sycl::cl_half(1.22) * cast<sycl::cl_half>(f1_dxnxiqhebvlxr(cast<sycl::cl_short8>(arg_1))) * sycl::cl_half(9.6);
    }
    v_o *= 54 * 51 + cast<sycl::cl_uchar>(v_wagx);
    v_o += 31;
    return sycl::cl_half(32.10);
  }
  v_wagx += double(91.47) + double(72.17);
  return cast<sycl::cl_half>(v_uepcf);
}
sycl::cl_ushort16 f1_dxnxiqhebvlxr(sycl::cl_short8 arg_1) {


  unsigned long v_p = 59;
  sycl::cl_long v_hz = v_p;

  switch (cast<size_t>(- 17 - f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(23.96)))) - 42)) {
    case 2:
      arg_1 -= cast<sycl::cl_short8>(v_p);
      break;
    case 77:
      v_hz = v_hz;
      break;
    case 6:
      arg_1 *= cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(arg_1) * cast<sycl::cl_double>(v_p))))) * cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(91.2) + cast<sycl::cl_double>(v_p))))) - sycl::cl_short8(17);
      for (v_p=18; v_p <= 63; v_p += 5) {


        longlong8 v_xb = longlong8(36);
        sycl::cl_double v_seg = cast<sycl::cl_double>(v_hz);
        float v_s = cast<float>(arg_1) * float(11.13) - float(11.85);

        v_hz -= 61;
        ++v_xb;
        {


          double v_qvr = double(77.88);
          sycl::cl_uchar3 v_wsycz = sycl::cl_uchar3(73);
          half8 v_k = cast<half8>(v_s);

          v_s -= float(61.64);
          for (v_s=20; v_s <= 32; v_s += 8) {

            unsigned int a1_fv[192] = {80};

            sycl::cl_double v_eybad = sycl::cl_double(96.20);
            sycl::cl_double3 v_d = cast<sycl::cl_double3>(v_s);

            switch (cast<size_t>(f1_irb(cast<sycl::cl_double>(f1_irb(v_eybad)) + cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(a1_fv[cast<size_t>(103-v_s)])))))) {
              case 44:
                v_qvr *= cast<double>(f1_irb(cast<sycl::cl_double>(a1_fv[cast<size_t>(v_s)])));
                v_xb = cast<longlong8>(v_hz) - longlong8(100);
                for (v_hz=v_s; v_hz > 0; v_hz--) {

                  sycl::cl_double a1_oocxbbkh[192] = {sycl::cl_double(65.3)};
                  sycl::cl_uchar a1_n[192] = {87};


                  {


                    unsigned int v_tch = cast<unsigned int>(v_s);

                    ; /* for-cycle skipped due to nesting limit */
                    v_d = cast<sycl::cl_double3>(v_s);
                    ; /* for-cycle skipped due to nesting limit */
                    return sycl::cl_ushort16(69);
                  }
                  v_eybad -= cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_p) + cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(v_seg))))))));
                  ++v_k;
                  return cast<sycl::cl_ushort16>(f1_irb(v_s));
                }
                break;

              default:
                v_seg += cast<sycl::cl_double>(v_hz) * v_qvr;
            }
            v_qvr++;
            switch (cast<size_t>(22)) {
              case 83:
                v_hz *= 92;
              case 82:
                if (cast<long long>(v_eybad)) {

                  sycl::cl_ushort a1_ep[192] = {46};
                  sycl::cl_double a1_nw[192] = {sycl::cl_double(42.51)};

                  sycl::cl_char v_db = 73;
                  sycl::cl_uchar v_gvg = 36;
                  uint2 v_pxdgfe = uint2(100);

                  v_eybad = sycl::cl_double(30.98);
                  ++arg_1;
                  for (v_hz=v_s; v_hz <= 63; ++v_hz) {

                    int3 a1_ed[192] = {int3(11)};
                    sycl::cl_half a1_g[192] = {sycl::cl_half(55.7)};

                    ulonglong8 v_vphq = ulonglong8(59) + ulonglong8(41);
                    double v_ziivorktar = double(66.43) + v_eybad;
                    sycl::cl_half v_hdabb = cast<sycl::cl_half>(v_xb);
                    sycl::cl_uchar v_bfj = cast<sycl::cl_uchar>(v_s) + 53;

                    v_gvg++;
                    v_db -= cast<sycl::cl_char>(v_seg);
                    ++v_xb;
                    return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(a1_fv[cast<size_t>(2*v_hz+v_hz)])));
                  }
                  return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(a1_fv[cast<size_t>(167-2*v_p)]))) + cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(copy(cast<sycl::cl_double>(v_gvg))))))));
                } else {

                  double a1_w[192] = {double(9.77)};

                  sycl::cl_double4 v_nn = cast<sycl::cl_double4>(v_eybad);
                  unsigned long v_wocb = 54;

                  v_d -= cast<sycl::cl_double3>(a1_w[cast<size_t>(166-2*v_s)]);
                  v_wocb *= cast<unsigned long>(arg_1);
                  v_wsycz *= cast<sycl::cl_uchar3>(f1_irb(cast<sycl::cl_double>(arg_1)));
                  return cast<sycl::cl_ushort16>(f1_irb(sycl::cl_double(100.31) + cast<sycl::cl_double>(a1_fv[cast<size_t>(v_s)])));
                }
              case 93:
                v_eybad += sycl::cl_double(66.13);
                v_wsycz -= sycl::cl_uchar3(99);
                break;

            }
            return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(a1_fv[cast<size_t>(91-v_p)])));
          }
          v_hz = 97;
          v_seg *= cast<sycl::cl_double>(v_hz);
          v_seg = v_s + sycl::cl_double(42.5);
          return cast<sycl::cl_ushort16>(v_seg) + cast<sycl::cl_ushort16>(f1_irb(sycl::cl_double(69.96)));
        }
        return cast<sycl::cl_ushort16>(v_p) * sycl::cl_ushort16(52);
      }
      break;
    case 99:
      v_hz += v_hz - f1_irb(cast<sycl::cl_double>(v_p) + cast<sycl::cl_double>(f1_irb(sycl::cl_double(45.21)))) - 6;
      break;
    case 11:
      switch (cast<size_t>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_hz) + cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(23.26) + cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_hz) + sycl::cl_double(74.84)))))))))))))))) {
        case 75:
          for (v_p=63; v_p > 0; --v_p) {

            sycl::cl_uchar4 a1_fld[192] = {sycl::cl_uchar4(56)};
            char2 a1_mlrxuwxvv[192] = {char2(5)};

            sycl::cl_half v_a = sycl::cl_half(72.71);

            arg_1 *= cast<sycl::cl_short8>(v_hz);
            if (v_p) {

              float a1_s[192] = {float(65.87)};

              sycl::cl_double v_fbl = cast<sycl::cl_double>(v_hz) + cast<sycl::cl_double>(v_hz);
              unsigned int v_k = 42;
              sycl::cl_char v_wo = - 94 - cast<sycl::cl_char>(v_fbl);

              v_k++;
              for (v_a=21; v_a <= 33; v_a++) {


                sycl::cl_uchar v_c = 12;
                longlong4 v_f = longlong4(9);
                sycl::cl_half v_ggpixzx = sycl::cl_half(25.40) + sycl::cl_half(69.54);

                for (v_wo=v_p; v_wo <= 63; v_wo += 7) {

                  sycl::cl_double8 a1_11[192] = {sycl::cl_double8(39)};
                  float a1_jw[192] = {float(39.14)};

                  sycl::cl_half v_u = sycl::cl_half(39.15);
                  unsigned short v_rrj = 54 + 37 + 63;
                  sycl::cl_float v_biff = sycl::cl_float(17.12) + cast<sycl::cl_float>(v_a);

                  v_f = cast<longlong4>(v_ggpixzx);
                  v_f = cast<longlong4>(f1_irb(cast<sycl::cl_double>(v_a))) - cast<longlong4>(v_ggpixzx) * cast<longlong4>(a1_11[cast<size_t>(181-v_a)]) + longlong4(79) - cast<longlong4>(f1_irb(cast<sycl::cl_double>(v_k)));
                  arg_1 += cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(v_c)));
                  return cast<sycl::cl_ushort16>(v_p) + cast<sycl::cl_ushort16>(v_p);
                }
                v_wo = f1_irb(cast<sycl::cl_double>(v_hz)) * cast<sycl::cl_char>(a1_s[cast<size_t>(v_a)]);
                v_c += cast<sycl::cl_uchar>(v_ggpixzx);
                for (v_wo=v_a; v_wo <= 63; ++v_wo) {

                  long a1_a[192] = {83};
                  sycl::cl_double a1_feq[192] = {sycl::cl_double(54.34)};

                  double v_m = cast<double>(v_a) - double(73.85);

                  v_ggpixzx += cast<sycl::cl_half>(v_f);
                  switch (cast<size_t>(f1_irb(cast<sycl::cl_double>(v_k) + sycl::cl_double(65.33)))) {
                    case 31:
                      v_ggpixzx = sycl::cl_half(77.14);
                      v_m += double(28.39);
                      v_hz *= 81;
                      break;
                    case 68:
                      v_f++;
                    case 87:
                      arg_1++;
                      v_m++;
                      arg_1 += cast<sycl::cl_short8>(f1_irb(cast<sycl::cl_double>(v_ggpixzx) + v_fbl));
                      v_fbl = (sycl::cl_double(84.27));
                      break;

                    default:
                      {

                        char16 a1_qmgkvkc[192] = {char16(37)};

                        sycl::cl_half v_z = sycl::cl_half(84.93);
                        sycl::cl_uchar v_xric = 53;
                        sycl::cl_double v_do = cast<sycl::cl_double>(v_xric);

                        v_fbl += sycl::cl_double(66.69);
                        v_k *= f1_irb(sycl::cl_double(75.2) + sycl::cl_double(9.99));
                        v_do = cast<sycl::cl_double>(f1_irb(sycl::cl_double(83.99)));
                        return cast<sycl::cl_ushort16>(v_wo) * sycl::cl_ushort16(99);
                      }
                  }
                  if (cast<sycl::cl_char>(v_ggpixzx)) {



                    v_fbl += sycl::cl_double(97.92);
                    v_hz += 2;
                    switch (cast<size_t>(100)) {
                      case 27:
                        v_k -= (cast<unsigned int>(arg_1));
                        v_hz = f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(51.31))))));
                      case 78:
                        ; /* for-cycle skipped due to nesting limit */
                        if (v_c) {

                          sycl::cl_int4 a1_zvlglqpfrzn[192] = {sycl::cl_int4(99)};
                          sycl::cl_char a1_q[192] = {28};

                          sycl::cl_float8 v_uhl = cast<sycl::cl_float8>(v_fbl) * sycl::cl_float8(97);
                          sycl::cl_short16 v_hwd = sycl::cl_short16(88);
                          sycl::cl_double16 v_i = sycl::cl_double16(12) - cast<sycl::cl_double16>(v_m);

                          ; /* for-cycle skipped due to nesting limit */
                          v_hwd = cast<sycl::cl_short16>(v_wo);
                          v_f = cast<longlong4>(f1_irb(sycl::cl_double(65.10))) - cast<longlong4>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(27.86)))))));
                          return cast<sycl::cl_ushort16>(v_fbl);
                        }
                        if (cast<sycl::cl_short>(v_m)) {

                          int16 a1_pcduccjg[192] = {int16(81)};
                          unsigned int a1_whu[192] = {88};

                          long4 v_wx = long4(60);

                          arg_1 = cast<sycl::cl_short8>(v_c);
                          switch (cast<size_t>(v_p)) {
                            case 68:
                              v_m++;
                            case 49:
                              v_hz = f1_irb(cast<sycl::cl_double>(v_c));
                              break;
                            case 14:
                              v_hz++;
                              v_ggpixzx -= cast<sycl::cl_half>(a1_feq[cast<size_t>(3*v_a)]);
                              break;
                            case 50:
                              ; /* for-cycle skipped due to nesting limit */
                              {


                                sycl::cl_int16 v_s = sycl::cl_int16(41);
                                sycl::cl_uchar v_r = cast<sycl::cl_uchar>(v_m);

                                ++v_hz;
                                v_wx *= cast<long4>(v_p);
                                v_fbl += sycl::cl_double(50.21) * cast<sycl::cl_double>(f1_irb(a1_feq[cast<size_t>(v_p)]));
                                return cast<sycl::cl_ushort16>(v_fbl);
                              }
                              arg_1 = sycl::cl_short8(22);
                              v_hz -= f1_irb(sycl::cl_double(18.4) + sycl::cl_double(91.86));

                            default:
                              v_ggpixzx = cast<sycl::cl_half>(f1_irb((cast<sycl::cl_double>(v_a))));
                              continue;
                          }
                          ; /* for-cycle skipped due to nesting limit */
                          v_k *= 80;
                          ; /* for-cycle skipped due to nesting limit */
                          return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(8.79)))));
                        } else {


                          sycl::cl_char v_pcizltxdn = cast<sycl::cl_char>(arg_1);

                          ; /* for-cycle skipped due to nesting limit */
                          v_pcizltxdn -= f1_irb(sycl::cl_double(42.14)) + f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(73.25) * sycl::cl_double(44.55) + cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_k))))))));
                          v_m = double(96.22);
                          return sycl::cl_ushort16(64);
                        }
                      case 52:
                        v_f += cast<longlong4>(f1_irb(v_fbl));
                        break;
                      case 16:
                        v_k += - 7;
                        break;

                    }
                    return sycl::cl_ushort16(8);
                  } else {

                    sycl::cl_ushort a1_uajbh[192] = {31};

                    sycl::cl_double v_ieo = sycl::cl_double(43.84);

                    v_c *= f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(30.82))) + sycl::cl_double(36.49));
                    ; /* for-cycle skipped due to nesting limit */
                    v_hz = f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(50.15) - cast<sycl::cl_double>(v_k))));
                    arg_1 += arg_1;
                    switch (cast<size_t>(v_hz)) {
                      case 73:
                        ++v_f;
                        break;

                    }
                    return sycl::cl_ushort16(95);
                  }
                  v_ggpixzx -= cast<sycl::cl_half>(f1_irb(sycl::cl_double(86.81)));
                  return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_a) + sycl::cl_double(63.80))) - cast<sycl::cl_double>(f1_irb(sycl::cl_double(19.54))))) * cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(49.75))))))) - cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(a1_mlrxuwxvv[cast<size_t>(3*v_a)]))))) + sycl::cl_ushort16(86);
                }
                return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(6.53)))));
              }
              v_k = 94 * cast<unsigned int>(v_a);
              return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(57.49) + sycl::cl_double(32.3))) + (cast<sycl::cl_double>(f1_irb(sycl::cl_double(34.26))), sycl::cl_double(64.47)) - cast<sycl::cl_double>(a1_fld[cast<size_t>(v_p)])));
            } else {

              sycl::cl_short3 a1_d[192] = {sycl::cl_short3(75)};

              float v_r = float(20.17);

              v_a = cast<sycl::cl_half>(f1_irb(sycl::cl_double(59.23))) * sycl::cl_half(24.49) + sycl::cl_half(63.66);
              v_a = cast<sycl::cl_half>(a1_fld[cast<size_t>(v_p)]);
              ++arg_1;
              return cast<sycl::cl_ushort16>(a1_d[cast<size_t>(v_p)]) + cast<sycl::cl_ushort16>(f1_irb(sycl::cl_double(95.67))) + cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_hz))))))) + cast<sycl::cl_double>(v_hz) + cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(6.49))))))))) - cast<sycl::cl_double>(v_a)))))));
            }
            v_a = cast<sycl::cl_half>(f1_irb(sycl::cl_double(82.26) - cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(f1_irb(sycl::cl_double(92.20)))))));
            v_hz -= f1_irb(cast<sycl::cl_double>(a1_mlrxuwxvv[cast<size_t>(69-v_p)]) * cast<sycl::cl_double>(v_a));
            return sycl::cl_ushort16(10);
          }
          break;
        case 95:
          if (v_hz) {


            ulonglong3 v_w = ulonglong3(95);
            long long v_oze = 86;
            float v_t = float(7.32);

            arg_1++;
            switch (cast<size_t>(- 49)) {
              case 59:
                v_w = cast<ulonglong3>(f1_irb(cast<sycl::cl_double>(v_w)));
                break;
              case 84:
                v_hz = f1_irb(cast<sycl::cl_double>(v_hz));

            }
            v_hz += cast<sycl::cl_long>(v_w);
            v_w += cast<ulonglong3>(v_p);
            return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(f1_irb(cast<sycl::cl_double>(v_p))) - cast<sycl::cl_double>(f1_irb(sycl::cl_double(35.6))))) + sycl::cl_ushort16(40) + cast<sycl::cl_ushort16>(arg_1);
          }

      }

    default:
      v_hz *= f1_irb(sycl::cl_double(40.29));
  }
  arg_1 = sycl::cl_short8(26);
  v_hz -= cast<sycl::cl_long>(arg_1) + v_hz + + cast<sycl::cl_long>(arg_1) + 13;
  return cast<sycl::cl_ushort16>(f1_irb(cast<sycl::cl_double>(v_hz) + cast<sycl::cl_double>(v_hz)));
}
unsigned int f1_irb(sycl::cl_double arg_1) {


  uint2 v_tih = uint2(4) + uint2(41);
  sycl::cl_uchar v_34 = 38 * 81;

  if (cast<char>(arg_1) || cast<sycl::cl_int>(v_tih)) {


    char2 v_fpsedw = cast<char2>(arg_1) * cast<char2>(arg_1);
    float v_jcjs = float(2.64);
    sycl::cl_uchar v_a = 97;

    v_a = v_34 + cast<sycl::cl_uchar>(arg_1);
    v_jcjs *= float(8.2);
    for (v_34=0; v_34 <= 63; v_34++) {

      sycl::cl_char a1_mdj[192] = {52};
      int a1_meq[192] = {86};

      sycl::cl_uchar v_n = 46;
      double v_hb = cast<double>(v_a);
      unsigned int v_e = 39;

      arg_1 *= sycl::cl_double(4.27);
      v_n -= 2;
      for (v_a=63; v_a > 0; --v_a) {



        ++v_hb;
        if (v_n) {

          sycl::cl_char a1_snomhvwjmbcgtrehro[192] = {10};
          unsigned int a1_wk[192] = {54};

          sycl::cl_char v_z = cast<sycl::cl_char>(arg_1);
          sycl::cl_double v_paiyzu = cast<sycl::cl_double>(v_34);

          v_n = 80;
          v_n -= v_a;
          for (v_paiyzu=0; v_paiyzu <= 56; v_paiyzu++) {

            unsigned int a1_wxpmxe[192] = {20};
            sycl::cl_short2 a1_h[192] = {sycl::cl_short2(94)};

            longlong2 v_xdgdn = cast<longlong2>(v_paiyzu);
            sycl::cl_char v_cmt = cast<sycl::cl_char>(v_jcjs) + - 30 - cast<sycl::cl_char>(v_fpsedw) + 71 - 94;
            sycl::cl_half v_xs = sycl::cl_half(11.51);

            v_xs *= sycl::cl_half(66.90) + cast<sycl::cl_half>(v_xs);
            {

              sycl::cl_half a1_fezv[192] = {sycl::cl_half(50.77)};
              long a1_rif[192] = {77};

              sycl::cl_int4 v_bic = sycl::cl_int4(36);
              sycl::cl_char v_tz = 53;

              v_tz = a1_meq[cast<size_t>(2*v_34)];
              arg_1 = sycl::cl_double(19.19) - (sycl::cl_double(37.72), sycl::cl_double(40.1) * sycl::cl_double(97.69) - sycl::cl_double(91.39));
              ; /* for-cycle skipped due to nesting limit */
              return 11;
            }
            v_cmt = v_a + cast<sycl::cl_char>(v_paiyzu) - 11 - 49;
            if (v_a) {

              sycl::cl_uchar a1_dbpxw[192] = {30};


              v_e++;
              ; /* for-cycle skipped due to nesting limit */
              v_xdgdn = cast<longlong2>(v_jcjs);
              return (45 + cast<unsigned int>(v_paiyzu) - 58, (v_34, 39 + v_a));
            }
            return 45;
          }
          return 42;
        } else {

          short3 a1_cjd[192] = {short3(80)};

          sycl::cl_double4 v_j = sycl::cl_double4(35) + sycl::cl_double4(30);
          ulonglong4 v_delvvj = ulonglong4(89);
          double v_h = double(70.69);
          long16 v_p = (long16(99) + cast<long16>(v_hb));

          v_hb += double(9.57);
          v_n -= 9 * v_e;
          ++v_tih;
          return 54;
        }
        v_tih = uint2(34);
        return 92;
      }
      return v_n;
    }
    return - cast<unsigned int>(v_fpsedw);
  } else {


    sycl::cl_char v_rv = 65;

    v_rv = 8 - 52;
    v_rv += - cast<sycl::cl_char>(arg_1) - + 6 + v_rv + 76;
    v_tih += cast<uint2>(arg_1);
    return 60;
  }
  arg_1 = sycl::cl_double(6.33);
  arg_1 *= cast<sycl::cl_double>(v_34);
  return v_34;
}

