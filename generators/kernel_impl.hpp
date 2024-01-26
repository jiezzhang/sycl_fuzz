// This is DPCPP
#if defined(REFRUN)
  #define CEAN_HEADER1(dim0) for (int cean0 = 0; cean0 != (dim0); ++ cean0) {
  #define CEAN_HEADER2(dim0, dim1) for (int cean0 = 0; cean0 != (dim0); ++ cean0) { for (int cean1 = 0; cean1 != (dim1); ++ cean1) {
  #define CEAN_HEADER3(dim0, dim1, dim2) for (int cean0 = 0; cean0 != (dim0); ++ cean0) { for (int cean1 = 0; cean1 != (dim1); ++ cean1) { for (int cean2 = 0; cean2 != (dim2); ++ cean2) {
  #define CI(idx,start,dim,step) start+cean##idx*(step)
  #define CEAN_FOOTER1 }
  #define CEAN_FOOTER2 }}
  #define CEAN_FOOTER3 }}}
#else
  #define CEAN_HEADER1(dim0)
  #define CEAN_HEADER2(dim0, dim1)
  #define CEAN_HEADER3(dim0, dim1, dim2)
  #define CI(idx,start,dim,step) start:dim:step
  #define CEAN_FOOTER1
  #define CEAN_FOOTER2
  #define CEAN_FOOTER3
#endif
#include "libcpp.h"
#include "type_cast.hpp"
#include <CL/sycl.hpp>
using namespace sycl;

short8 f3_ji(float, unsigned int, sycl::cl_half);
sycl::cl_char f1_gs(sycl::cl_uchar);
sycl::cl_float4 f2_aqekdde(sycl::cl_ulong, sycl::cl_char);
sycl::cl_long f0_acrsf();
sycl::cl_ulong16 f2_ag(sycl::cl_ushort, int);
sycl::cl_int f1_k(sycl::cl_char);

template <typename T, int dims, sycl::access::mode mode,
          sycl::access::target target, sycl::access::placeholder placeholder>
void kernel_fun(sycl::nd_item<dims> item,
                sycl::accessor<T, dims, mode, target, placeholder> result) {
  sycl::cl_float v_xijzkng =
      sycl::cl_float(5.86) + sycl::cl_float(37.63) +
      sycl::cl_float(90.78) *
          cast<sycl::cl_float>(result[item.get_global_linear_id()]) +
      sycl::cl_float(10.23) + sycl::cl_float(77.13) + sycl::cl_float(25.15);
  long16 v_g = long16(13);

  v_xijzkng += cast<sycl::cl_float>(result[item.get_global_linear_id()]);
  for (v_xijzkng=11; v_xijzkng <= 55; v_xijzkng++) {

    unsigned int v_o = 6;
    double v_akcw = double(43.31);

    {

      double a1_gypo[192] = {double(69.58)};
      long3 a1_ydy[192] = {long3(81)};

      unsigned int v_ptuf = cast<unsigned int>(v_xijzkng);
      sycl::cl_char4 v_sek = sycl::cl_char4(71);

      v_akcw = cast<double>(a1_ydy[cast<size_t>(v_xijzkng)]);
      for (result[item.get_global_linear_id()]=63; result[item.get_global_linear_id()] > 25; --result[item.get_global_linear_id()]) {

        double16 a1_j[192] = {double16(82)};
        sycl::cl_long8 a1_w[192] = {sycl::cl_long8(59)};

        v_ptuf = cast<unsigned int>(v_xijzkng) + v_o;
        a1_gypo[cast<size_t>(result[item.get_global_linear_id()])] =
            cast<double>(f1_k((
                (f1_k(cast<sycl::cl_char>(f2_ag(v_ptuf, cast<int>(v_xijzkng)))),
                 (v_o ? (33) / v_o : (93))) +
                (result[item.get_global_linear_id()],
                 cast<sycl::cl_char>(f2_aqekdde(
                     f1_gs(cast<sycl::cl_uchar>(f3_ji(
                         v_akcw, cast<unsigned int>(v_xijzkng),
                         cast<sycl::cl_half>(v_o) + cast<sycl::cl_half>(v_o)))),
                     81))))));
        a1_w[cast<size_t>(2 * result[item.get_global_linear_id()])] +=
            cast<sycl::cl_long8>(f2_ag(80, f1_gs(75) + v_ptuf));
        v_akcw =
            cast<double>(f2_aqekdde(f1_k(cast<sycl::cl_char>(f2_ag(
                                        cast<sycl::cl_ushort>(v_xijzkng), 72))),
                                    f1_k(7)));
        v_sek *= cast<sycl::cl_char4>(f2_aqekdde(
                     (cast<sycl::cl_ulong>(f2_aqekdde(5, v_o + 18)), v_o),
                     cast<sycl::cl_char>(v_xijzkng))) -
                 cast<sycl::cl_char4>(v_akcw);
      }
      v_o++;
      v_akcw = double(65.96);
      v_g = long16(19);
    }
    for (v_akcw=3; v_akcw <= 32; v_akcw++) {

      unsigned int a1_sm[192] = {50};

      sycl::cl_float v_nu =
          sycl::cl_float(67.59) + sycl::cl_float(30.90) -
          cast<sycl::cl_float>(result[item.get_global_linear_id()]);

      break;
      ++v_o;
      v_g += long16(78);
    }
    for (result[item.get_global_linear_id()]=0; result[item.get_global_linear_id()] <= 63; result[item.get_global_linear_id()]++) {

      unsigned int a1_n[192] = {79};
      unsigned int a1_tek[192] = {43};

      unsigned int v_d = 91;
      sycl::cl_half8 v_a = sycl::cl_half8(79) - sycl::cl_half8(44);
      sycl::cl_double v_nenaadmts = sycl::cl_double(18.51);

      a1_n[cast<size_t>(result[item.get_global_linear_id()])] = result[item.get_global_linear_id()];
      v_g *= cast<long16>(v_akcw);
      for (v_akcw=8; v_akcw <= 39; v_akcw += 1) {

        half4 v_xppa = cast<half4>(v_a);
        int v_irdvsi = 34;
        unsigned int v_izllfxke = 53;
        sycl::cl_char8 v_uk = sycl::cl_char8(6) + sycl::cl_char8(25);

        v_nenaadmts += sycl::cl_double(84.85);
        v_d = cast<unsigned int>(v_nenaadmts) + cast<unsigned int>(v_akcw);
        v_d *= 52 + v_o;
      }
      continue;
      v_nenaadmts = v_xijzkng;
    }
  }
  for (result[item.get_global_linear_id()]=0; result[item.get_global_linear_id()] <= 63; result[item.get_global_linear_id()]++) {

    long a1_xlgut[192] = {12};

    {

      sycl::cl_uchar a1_lmeh[192] = {90};

      float v_p = float(64.7);
      float v_b = (cast<char>(v_xijzkng) ? v_p : (float(19.10)) + float(51.45)) * float(80.14);
      sycl::cl_half4 v_yxadum = sycl::cl_half4(100);

      v_yxadum *=
          copy(cast<sycl::cl_half4>(result[item.get_global_linear_id()]));
      v_p = cast<float>(f0_acrsf());
      v_g++;
    }
    if (result[item.get_global_linear_id()] ||
        cast<sycl::cl_ushort>(v_xijzkng) ||
        (result[item.get_global_linear_id()])) {

      sycl::cl_double16 a1_cm[192] = {sycl::cl_double16(87)};

      sycl::cl_uchar2 v_10 = sycl::cl_uchar2(3);
      longlong8 v_zxt = longlong8(87) * longlong8(62);
      sycl::cl_half2 v_timcq = sycl::cl_half2(3);
      short v_mnu = 21;

      for (v_mnu = 58; v_mnu <= 63; --v_mnu) {

        double4 a1_e[192] = {double4(29)};

        sycl::cl_double v_nwf = sycl::cl_double(17.36);
        sycl::cl_half v_io = sycl::cl_half(41.96);
        sycl::cl_half v_a =
            sycl::cl_half(2.72) * sycl::cl_half(97.82) - sycl::cl_half(14.90);

        for (v_xijzkng = 63; v_xijzkng > 24; v_xijzkng--) {

          sycl::cl_float a1_jos[192] = {sycl::cl_float(20.64)};
          sycl::cl_float4 a1_qs[192] = {sycl::cl_float4(35)};

          sycl::cl_char8 v_cc = sycl::cl_char8(96);
          sycl::cl_half v_eav = cast<sycl::cl_half>(v_io);
          sycl::cl_float v_yiqnwmi = sycl::cl_float(15.14);

          ++v_io;
          v_cc *= cast<sycl::cl_char8>(v_a);
          v_a = cast<sycl::cl_half>(f1_gs(33)) + cast<sycl::cl_half>(v_eav);
        }
        v_xijzkng *= v_nwf;
        v_10++;
      }
      a1_cm[cast<size_t>(result[item.get_global_linear_id()])] =
          cast<sycl::cl_double16>(f0_acrsf()) *
              cast<sycl::cl_double16>(f2_aqekdde(53, 3)) +
          sycl::cl_double16(20);
      v_zxt = (cast<longlong8>(v_mnu), cast<longlong8>(f0_acrsf()));
      for (v_xijzkng = 2; v_xijzkng <= 63; ++v_xijzkng) {

        sycl::cl_int3 v_tswx = sycl::cl_int3(19);

        v_zxt += cast<longlong8>(result[item.get_global_linear_id()]);
        v_zxt = cast<longlong8>(
            f2_ag(cast<sycl::cl_ushort>(v_xijzkng) +
                      cast<sycl::cl_ushort>(f2_aqekdde(
                          cast<sycl::cl_ulong>(v_xijzkng), f0_acrsf())),
                  result[item.get_global_linear_id()] * f1_gs(v_mnu * -3)));
        switch (cast<size_t>(result[item.get_global_linear_id()])) {
        case 44:
          v_mnu = 43 * v_mnu +
                  f1_k(cast<sycl::cl_char>(f2_ag(6, cast<int>(v_xijzkng))));
          break;
        }
        v_10 *= cast<sycl::cl_uchar2>(v_xijzkng) +
                cast<sycl::cl_uchar2>(a1_xlgut[cast<size_t>(
                    3 * result[item.get_global_linear_id()])]) +
                cast<sycl::cl_uchar2>(
                    f2_aqekdde(cast<sycl::cl_ulong>(v_xijzkng), 16 + 34));
      }
      v_xijzkng = sycl::cl_float(38.63);

    } else {

      sycl::cl_uchar8 v_rfn =
          (cast<int>(v_xijzkng)
               ? sycl::cl_uchar8(12) + cast<sycl::cl_uchar8>(v_xijzkng) +
                     sycl::cl_uchar8(53)
               : sycl::cl_uchar8(79)) -
          cast<sycl::cl_uchar8>(result[item.get_global_linear_id()]);

      v_g -= cast<long16>(result[item.get_global_linear_id()]) +
             cast<long16>(f2_aqekdde(
                 result[item.get_global_linear_id()] -
                     result[item.get_global_linear_id()],
                 cast<sycl::cl_char>(
                     f3_ji(cast<float>(v_rfn) + v_xijzkng, 49,
                           sycl::cl_half(79.8) +
                               cast<sycl::cl_half>(
                                   result[item.get_global_linear_id()]))))) +
             cast<long16>(result[item.get_global_linear_id()]);
      v_g -= cast<long16>(
          f3_ji(cast<float>(f0_acrsf()) + float(87.75) + float(84.61),
                cast<unsigned int>(
                    f3_ji(cast<float>(a1_xlgut[cast<size_t>(
                              96 + result[item.get_global_linear_id()] -
                              result[item.get_global_linear_id()])]) -
                              v_xijzkng,
                          f1_gs(cast<sycl::cl_uchar>(v_xijzkng) -
                                f1_k(cast<sycl::cl_char>(v_xijzkng))),
                          cast<sycl::cl_half>(f0_acrsf()))),
                cast<sycl::cl_half>(result[item.get_global_linear_id()])));
      v_xijzkng *= v_xijzkng;
    }
    v_g = +cast<long16>(f2_ag(
        result[item.get_global_linear_id()],
        cast<int>(f3_ji(
            v_xijzkng,
            cast<unsigned int>(f2_ag(
                f1_gs(f1_gs((cast<long>(v_xijzkng)
                                 ? 30
                                 : result[item.get_global_linear_id()] * 59 *
                                       cast<sycl::cl_uchar>(v_g)))) +
                    f0_acrsf(),
                cast<int>(f2_aqekdde(
                    f1_gs(88) - +f1_gs(25 + 95) *
                                    f1_k(cast<sycl::cl_char>(v_xijzkng)),
                    f1_gs(+cast<sycl::cl_uchar>(f3_ji(
                        cast<float>(f2_aqekdde(
                            38 * f0_acrsf(),
                            cast<sycl::cl_char>(f2_ag(
                                cast<sycl::cl_ushort>(v_g),
                                a1_xlgut[cast<size_t>(
                                    result[item.get_global_linear_id()])] +
                                    35)))) +
                            cast<float>(f0_acrsf()),
                        5,
                        cast<sycl::cl_half>(
                            f3_ji(cast<float>(v_g),
                                  result[item.get_global_linear_id()],
                                  cast<sycl::cl_half>(f0_acrsf()))) +
                            cast<sycl::cl_half>(f0_acrsf())))))))),
            sycl::cl_half(79.100))) +
            87));
    for (v_xijzkng=0; v_xijzkng <= 62; ++v_xijzkng) {

      sycl::cl_uchar v_ke = cast<sycl::cl_uchar>(v_xijzkng) * 92;
      sycl::cl_float v_y = cast<sycl::cl_float>(v_ke) + sycl::cl_float(91.84);
      double v_r = double(88.76);

      a1_xlgut[cast<size_t>(v_xijzkng)] += cast<long>(f2_aqekdde(
          cast<sycl::cl_ulong>(v_xijzkng),
          cast<sycl::cl_char>(
              f2_ag(cast<sycl::cl_ushort>(f2_aqekdde(cast<sycl::cl_ulong>(v_r),
                                                     cast<sycl::cl_char>(v_y))),
                    f1_k(24)))));
      v_ke -= 17;
      v_g *= (cast<short>(v_g) ? long16(2) : long16(80));
      v_r -= cast<double>(f1_gs(9)) + v_xijzkng;
    }
    a1_xlgut[cast<size_t>(2*result[item.get_global_linear_id()]+result[item.get_global_linear_id()])] -= 14;
  }
  result[item.get_global_linear_id()] -= cast<unsigned long>(v_g);
}
short8 f3_ji(float arg_3, unsigned int arg_2, sycl::cl_half arg_1) {

  sycl::cl_float v_o = sycl::cl_float(67.48) + cast<sycl::cl_float>(arg_2);

  arg_2++;
  arg_2 = arg_2;
  arg_3 = float(21.18);
  return cast<short8>(v_o) - short8(20);
}
sycl::cl_char f1_gs(sycl::cl_uchar arg_1) {

  double a1_tmirhclrp[192] = {double(27.46)};
  ushort8 a1_r[192] = {ushort8(71)};

  for (arg_1=63; arg_1 <= 63; --arg_1) {

    double v_mok = double(28.20);

    for (v_mok=arg_1; v_mok <= arg_1; ++v_mok) {

      sycl::cl_char v_cxt = 82;

      v_cxt -= -(cast<sycl::cl_char>(v_mok)
                     ? (cast<sycl::cl_char>(v_mok) + f0_acrsf()) /
                           cast<sycl::cl_char>(v_mok)
                     : (85));
      continue;
      v_cxt = arg_1 + v_cxt;
      v_cxt = v_cxt;
      v_cxt = 48 + v_cxt;
      return cast<sycl::cl_char>(
          f2_ag(v_cxt - cast<sycl::cl_ushort>(f2_aqekdde(93, 58)), 71));
    }
    v_mok = double(59.19);
    v_mok = double(73.69);
    return 25;
  }
  arg_1 = 73;
  arg_1 = 67;
  return 9;
}
sycl::cl_float4 f2_aqekdde(sycl::cl_ulong arg_2, sycl::cl_char arg_1) {

  arg_2 = 67;
  arg_1 = 8;
  arg_1 = 75;
  return sycl::cl_float4(70);
}
sycl::cl_long f0_acrsf() {

  int a1_35[192] = {9};
  int a1_85[192] = {87};

  int v_76 = 65;
  int v_40 = 4;
  int v_80 = 41;
  int v_66 = 18;

  v_40 = 23;
  v_80 = 57;
  v_66 = 10;
  return 12;
}
sycl::cl_ulong16 f2_ag(sycl::cl_ushort arg_2, int arg_1) {

  int a1_48[192] = {12};
  int a1_34[192] = {51};

  int v_34 = 81;
  int v_50 = 74;

  arg_2 = 24;
  v_34 = 89;
  arg_2 = 21;
  return sycl::cl_ulong16(99);
}
sycl::cl_int f1_k(sycl::cl_char arg_1) {

  int v_88 = 54;

  arg_1 = 3;
  arg_1 = 87;
  v_88 = 50;
  return 49;
}
