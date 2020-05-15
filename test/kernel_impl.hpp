// This is C++
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
using namespace cl::sycl;


double f2_i(cl::sycl::cl_uchar, cl::sycl::cl_char2);
cl::sycl::cl_char3 f3_s(cl::sycl::cl_long16, unsigned int, cl::sycl::cl_char);
cl::sycl::cl_double f3_ris(cl::sycl::cl_half, cl::sycl::cl_half, double16);
cl::sycl::cl_uint3 f3_p(cl::sycl::cl_char, unsigned long long, cl::sycl::cl_float8);
ushort16 f0_nlf();
double f0_ik();

template <typename T, int dims, cl::sycl::access::mode mode,
        cl::sycl::access::target target, cl::sycl::access::placeholder placeholder>
void kernel_fun(cl::sycl::nd_item<dims> item, cl::sycl::accessor<T, dims, mode, target, placeholder> result)
{
  cl::sycl::cl_ulong v_ko = result[item.get_global_linear_id()];
  int v_umusb = 96 + 43;
  
  ; /* break statement was omited here */
  result[item.get_global_linear_id()] = cast<unsigned long>(f2_i(v_umusb, cl::sycl::cl_char2(66)));
  ; /* break statement was omited here */
  for (v_umusb=3; v_umusb <= 63; v_umusb++) {
    cl::sycl::cl_ulong2 a1_qk[192];
    
    cl::sycl::cl_uint8 v_hitcrzdyf = cl::sycl::cl_uint8(63);
    
    v_ko++;
    {
      cl::sycl::cl_float a1_e[192];
      cl::sycl::cl_long3 a1_yyn[192];
      
      unsigned long v_k = v_ko;
      cl::sycl::cl_float v_c = 24.42;
      unsigned int v_sgn = 88;
      float v_zgk = cast<float>(v_umusb);
      
      for (v_sgn=15; v_sgn <= v_umusb; ++v_sgn) {
        cl::sycl::cl_uchar a1_l[192];
        
        double16 v_gyll = double16(10);
        cl::sycl::cl_int8 v_bytwj = cl::sycl::cl_int8(95);
        
        result[item.get_global_linear_id()]++;
        for (result[item.get_global_linear_id()]=0; result[item.get_global_linear_id()] <= 63; ++result[item.get_global_linear_id()]) {
          
          cl::sycl::cl_uchar v_rf = (v_ko ? 98 : cast<cl::sycl::cl_uchar>(v_hitcrzdyf));
          cl::sycl::cl_char v_x = 46;
          unsigned int v_z = 48;
          float v_bcfqxb = cast<float>(v_rf);
          
          v_k -= cast<unsigned long>(f0_nlf()) + cast<unsigned long>(v_c);
          ; /* for-cycle skipped due to nesting limit */
          ++v_ko;
          v_rf++;
          
        }
        v_bytwj *= cl::sycl::cl_int8(86);
        v_k *= cast<unsigned long>(f0_ik()) + v_k;
        v_k += a1_l[cast<size_t>(2*v_umusb+v_umusb)];
        
      }
      if (v_umusb || result[item.get_global_linear_id()]) {
        cl::sycl::cl_half a1_hef[192];
        cl::sycl::cl_double2 a1_jf[192];
        
        float v_ryg = 83.62;
        
        v_zgk++;
        ++v_ko;
        v_sgn -= cast<unsigned int>(f3_ris(25.100, 9.69, double16(58) + cast<double16>(v_sgn)));
        
      }
      a1_qk[cast<size_t>(v_umusb)] = cast<cl::sycl::cl_ulong2>(f0_ik());
      
    }
    v_ko -= cast<cl::sycl::cl_ulong>(f3_s(cast<cl::sycl::cl_long16>(f2_i(61, cast<cl::sycl::cl_char2>(f0_nlf()))), v_umusb + cast<unsigned int>(f3_p(59, 25, cast<cl::sycl::cl_float8>(a1_qk[cast<size_t>(v_umusb)]))) + v_umusb, cast<cl::sycl::cl_char>(f0_nlf())));
    
  }
  v_umusb = cast<int>(f3_ris(cast<cl::sycl::cl_half>(f3_s(cast<cl::sycl::cl_long16>(f2_i(cast<cl::sycl::cl_uchar>(f2_i(cast<cl::sycl::cl_uchar>(f3_ris(f2_i(result[item.get_global_linear_id()], cl::sycl::cl_char2(17)) * cast<cl::sycl::cl_half>(f3_s(! cl::sycl::cl_long16(3), 64, result[item.get_global_linear_id()])), 42.65, cast<double16>(f3_p(12 + 22, 87, cast<cl::sycl::cl_float8>(f2_i(cast<cl::sycl::cl_uchar>(f0_ik()) + (result[item.get_global_linear_id()] ? v_umusb : 2), cast<cl::sycl::cl_char2>(f0_ik()))))) + double16(21) + cast<double16>(v_ko))), (v_ko ? cast<cl::sycl::cl_char2>(v_umusb) : cl::sycl::cl_char2(67) + cast<cl::sycl::cl_char2>(v_umusb)))) - cast<cl::sycl::cl_uchar>(f3_p(cast<cl::sycl::cl_char>(f2_i(58, cl::sycl::cl_char2(79))) + v_umusb - 20 - (3, cast<cl::sycl::cl_char>(f3_s(cast<cl::sycl::cl_long16>(f3_s(cast<cl::sycl::cl_long16>(f3_ris(62.53 * cast<cl::sycl::cl_half>(v_umusb), 20.9, cast<double16>(v_umusb))), cast<unsigned int>(f3_s(cl::sycl::cl_long16(34), v_ko + cast<unsigned int>(f3_s(cast<cl::sycl::cl_long16>(result[item.get_global_linear_id()]) + cast<cl::sycl::cl_long16>(f3_p(cast<cl::sycl::cl_char>(f2_i(cast<cl::sycl::cl_uchar>(f3_p(cast<cl::sycl::cl_char>(f3_p(22, 72, cast<cl::sycl::cl_float8>(result[item.get_global_linear_id()]))), 78, cl::sycl::cl_float8(95))), cast<cl::sycl::cl_char2>(f0_nlf()))), v_umusb + cast<unsigned long long>(f3_s(cast<cl::sycl::cl_long16>(v_ko), 99, result[item.get_global_linear_id()])), cl::sycl::cl_float8(26) + cast<cl::sycl::cl_float8>(f3_p(cast<cl::sycl::cl_char>(f3_ris(92.45, f0_ik() * f0_ik() + f2_i(cast<cl::sycl::cl_uchar>(f3_ris(cast<cl::sycl::cl_half>(f0_nlf()), cast<cl::sycl::cl_half>(v_ko), double16(47))) * 14, cast<cl::sycl::cl_char2>(f0_ik())), double16(99))), (result[item.get_global_linear_id()] ? result[item.get_global_linear_id()] : 61), cl::sycl::cl_float8(77))))), result[item.get_global_linear_id()] + 30, cast<cl::sycl::cl_char>(f3_s(cast<cl::sycl::cl_long16>(result[item.get_global_linear_id()]), 94, cast<cl::sycl::cl_char>(f0_nlf()) + v_umusb)))) - 67, 16)) + cast<unsigned int>(f0_ik()), 27 - (97, 98))), 88, (51 ? result[item.get_global_linear_id()] + result[item.get_global_linear_id()] : 74) - 5))), v_umusb, cl::sycl::cl_float8(98))), cast<cl::sycl::cl_char2>(v_umusb))), result[item.get_global_linear_id()], 46)), cast<cl::sycl::cl_half>(v_ko) - f3_ris(cast<cl::sycl::cl_half>(v_umusb), 98.77, cast<double16>(f3_s(cl::sycl::cl_long16(49), (result[item.get_global_linear_id()] ? 53 : 59), 49)) + cast<double16>(result[item.get_global_linear_id()])), double16(59))) - cast<int>(f3_s(cast<cl::sycl::cl_long16>(v_ko), v_umusb, cast<cl::sycl::cl_char>(f2_i(89, cl::sycl::cl_char2(88) - cl::sycl::cl_char2(77))) + cast<cl::sycl::cl_char>(f3_s(cl::sycl::cl_long16(11), v_ko, 94 + 76 + (((38 ? v_ko : cast<cl::sycl::cl_char>(f3_ris(5.9 - cast<cl::sycl::cl_half>(f3_p(86, cast<unsigned long long>(f0_ik()), cl::sycl::cl_float8(43))), f3_ris(49.21, f0_ik() + cast<cl::sycl::cl_half>(f3_s(copy(cast<cl::sycl::cl_long16>(result[item.get_global_linear_id()])), 30, 74 + cast<cl::sycl::cl_char>(f3_ris(85.12, cast<cl::sycl::cl_half>(v_umusb), cast<double16>(v_umusb) - cast<double16>(f3_p(53, cast<unsigned long long>(f0_nlf()), cast<cl::sycl::cl_float8>(f0_ik()))) + cast<double16>(v_umusb))))), double16(56)) + 76.49, cast<double16>(f0_nlf()) * double16(92)))), cast<cl::sycl::cl_char>(f3_ris(f3_ris(f3_ris(f3_ris(1.29, cast<cl::sycl::cl_half>(result[item.get_global_linear_id()]), double16(76)), cast<cl::sycl::cl_half>(f3_s(cast<cl::sycl::cl_long16>(f0_ik()) - cl::sycl::cl_long16(67), cast<unsigned int>(f3_ris(40.40, cast<cl::sycl::cl_half>(v_umusb), double16(39))) + v_ko + result[item.get_global_linear_id()] + cast<unsigned int>(f0_ik()), cast<cl::sycl::cl_char>(f3_ris(cast<cl::sycl::cl_half>(result[item.get_global_linear_id()]) + cast<cl::sycl::cl_half>(v_ko), cast<cl::sycl::cl_half>(result[item.get_global_linear_id()]), cast<double16>(v_ko))))), double16(57)), 20.10 * 10.78, cast<double16>(f3_s(cl::sycl::cl_long16(7), 69, v_ko)) + cast<double16>(f0_nlf())), f0_ik(), double16(56)))), v_umusb) + 21))));
}
double f2_i(cl::sycl::cl_uchar v_mz, cl::sycl::cl_char2 v_x) {
  
  cl::sycl::cl_uint2 v_vknqt = cl::sycl::cl_uint2(17);
  ushort8 v_m = cast<ushort8>(v_mz);
  cl::sycl::cl_char v_syv = 55;
  cl::sycl::cl_long v_o = cast<cl::sycl::cl_long>(v_m);
  
  {
    
    cl::sycl::cl_char v_dw = v_x;
    float4 v_u = float4(24);
    cl::sycl::cl_char v_u = 96 * 74 - 81 + 43 + 56;
    float v_ejwympnn = 34.80;
    
    v_syv *= 67;
    v_dw = 12;
    ; /* continue statement was omited here */
    v_u *= 55 - cast<cl::sycl::cl_char>(f3_s(cast<cl::sycl::cl_long16>(v_x), 99, 93 + cast<cl::sycl::cl_char>(f3_ris(15.49 - cast<cl::sycl::cl_half>(f3_p(cast<cl::sycl::cl_char>(f3_ris(35.9, f3_ris(cast<cl::sycl::cl_half>(v_x), f0_ik() + (cast<cl::sycl::cl_half>(f0_nlf()), v_ejwympnn + cast<cl::sycl::cl_half>(v_x)), cast<double16>(f3_p(v_x, (cast<unsigned long long>(v_mz)? (cast<unsigned long long>(f0_nlf())) / cast<unsigned long long>(v_mz) : (v_o)), cast<cl::sycl::cl_float8>(v_u) * cast<cl::sycl::cl_float8>(f0_ik())))), cast<double16>(v_ejwympnn))), v_o, cast<cl::sycl::cl_float8>(v_dw))), 29.51, double16(61)))));
    {
      int a1_24[192];
      
      int v_n = 5;
      cl::sycl::cl_uchar v_z = 75;
      cl::sycl::cl_uchar v_t = 20;
      
      v_n = 20;
      v_n = 6;
      v_dw = 52;
      return 98.64;
    }
    v_mz = 17.75;
    return 41.84;
  }
  v_vknqt = cl::sycl::cl_uint2(76);
  v_m = ushort8(46);
  return 62.33;
}
cl::sycl::cl_char3 f3_s(cl::sycl::cl_long16 v_61, unsigned int v_70, cl::sycl::cl_char v_54) {
  int a1_95[192];
  
  
  v_61 = 12;
  v_61 = 51;
  v_54 = 45;
  return cl::sycl::cl_char3(13);
}
cl::sycl::cl_double f3_ris(cl::sycl::cl_half v_77, cl::sycl::cl_half v_53, double16 v_38) {
  int a1_68[192];
  int a1_100[192];
  
  int v_26 = 36;
  int v_33 = 80;
  int v_3 = 30;
  int v_30 = 20;
  
  v_38 = 58;
  v_26 = 21;
  v_53 = 97;
  return 57.79;
}
cl::sycl::cl_uint3 f3_p(cl::sycl::cl_char v_61, unsigned long long v_87, cl::sycl::cl_float8 v_17) {
  int a1_21[192];
  int a1_5[192];
  
  int v_64 = 93;
  int v_59 = 77;
  int v_33 = 80;
  
  v_87 = 17;
  v_87 = 33;
  v_87 = 10;
  return cl::sycl::cl_uint3(89);
}
ushort16 f0_nlf() {
  int a1_89[192];
  
  int v_14 = 82;
  int v_8 = 37;
  int v_83 = 50;
  int v_93 = 11;
  
  v_83 = 58;
  v_14 = 44;
  v_8 = 37;
  return ushort16(85);
}
double f0_ik() {
  int a1_1[192];
  
  int v_15 = 89;
  int v_61 = 32;
  int v_65 = 21;
  int v_38 = 74;
  
  v_15 = 64;
  v_65 = 43;
  v_65 = 98;
  return 67.70;
}

