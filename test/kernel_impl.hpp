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


cl::sycl::cl_uchar f2_snetg(cl::sycl::cl_uchar, cl::sycl::cl_double);
float f3_ncay(unsigned int, unsigned int, unsigned int);
cl::sycl::cl_float f0_kzlgo();
cl::sycl::cl_half f2_fum(cl::sycl::cl_float, float);
cl::sycl::cl_char f1_wkrb(int);
cl::sycl::cl_half f3_q(int, cl::sycl::cl_uchar, cl::sycl::cl_char);

template <typename T, int dims, cl::sycl::access::mode mode,
        cl::sycl::access::target target, cl::sycl::access::placeholder placeholder>
void kernel(cl::sycl::nd_item<dims> item, cl::sycl::accessor<T, dims, mode, target, placeholder> result)
{
  cl::sycl::cl_char v_y = result[item.get_global_linear_id()];
  double v_cn = 50.76;
  cl::sycl::cl_char v_q = 5;
  
  switch (cast<size_t>(v_y)) {
    case 23: 
      v_cn = (v_y ? 32.7 - 23.85 : v_y * (8.67));
      break;    
    case 94: 
      ; /* for-cycle skipped due to nesting limit */
      break;    
    
    default: 
      switch (cast<size_t>(v_q)) {
        case 2: 
          ; /* for-cycle skipped due to nesting limit */
          v_q = v_y;
          result[item.get_global_linear_id()] *= 17 + 63;        
        case 100: 
          result[item.get_global_linear_id()]++;
          v_y = (v_q? (11) / v_q : (v_q));
          break;        
        case 73: 
          result[item.get_global_linear_id()] = 82;
          switch (cast<size_t>(25)) {
            case 39: 
              result[item.get_global_linear_id()] = 100 + 45;            
            case 69: 
              v_q -= 98;            
            case 3: 
              result[item.get_global_linear_id()] -= 15;
              if (v_y) {
                
                cl::sycl::cl_float v_jt = result[item.get_global_linear_id()];
                int v_ru = 95 + result[item.get_global_linear_id()] + 15 + 41;
                cl::sycl::cl_float v_gmqcvm = 72.60;
                
                ; /* for-cycle skipped due to nesting limit */
                v_cn = v_y + result[item.get_global_linear_id()];
                v_q += 59;
                
              } else {
                cl::sycl::cl_float a1_gyfzd[192];
                
                cl::sycl::cl_char v_dec = (cast<long long>(v_cn)? (50) / cast<long long>(v_cn) : (86 + result[item.get_global_linear_id()])) || (cast<long long>(v_cn)? (result[item.get_global_linear_id()] + 96 + 31 + 55) / cast<long long>(v_cn) : (37));
                cl::sycl::cl_float v_ndm = 63.30;
                
                ; /* for-cycle skipped due to nesting limit */
                ; /* for-cycle skipped due to nesting limit */
                result[item.get_global_linear_id()] = 46;
                
              }
              break;            
            case 66: 
              result[item.get_global_linear_id()] = 76 + 100;
              break;            
            
          }
          ; /* for-cycle skipped due to nesting limit */
          break;        
        
        default: 
          v_cn = v_cn;
      }
      ; /* continue statement was omited here */
  }
  ; /* for-cycle skipped due to nesting limit */
  v_q = 68;
}
cl::sycl::cl_uchar f2_snetg(cl::sycl::cl_uchar v_zizrjpa, cl::sycl::cl_double v_orsonpu) {
  float a1_wd[192];
  
  cl::sycl::cl_float v_zoo = v_zizrjpa;
  cl::sycl::cl_char v_iucpasq = 54;
  unsigned int v_j = 6;
  cl::sycl::cl_half v_ucx = v_j;
  
  ; /* for-cycle skipped due to nesting limit */
  {
    
    cl::sycl::cl_char v_bb = 96;
    
    if (v_bb) {
      
      cl::sycl::cl_half v_s = v_orsonpu;
      cl::sycl::cl_double v_oxxwilnd = (v_zizrjpa ? v_zoo : 52.56);
      cl::sycl::cl_float v_op = 84.32;
      
      v_zoo = 56.89;
      v_iucpasq -= 9 + 56;
      v_oxxwilnd -= 32.59 + 5.50;
      return 76;
    }
    v_orsonpu -= v_zoo;
    v_ucx = 68.3 + 73.8;
    return v_iucpasq;
  }
  v_orsonpu *= v_ucx;
  return v_j;
}
float f3_ncay(unsigned int v_lsbk, unsigned int v_w, unsigned int v_qeoah) {
  
  float v_n = 90.81;
  
  v_n *= 78.55;
  v_w += v_w;
  v_qeoah = 99.78;
  return 59.41 + 29.76;
}
cl::sycl::cl_float f0_kzlgo() {
  double a1_ih[192];
  unsigned short a1_n[192];
  
  
  if (16) {
    double a1_v[192];
    int a1_qf[192];
    
    
    ; /* for-cycle skipped due to no free lvals variables */
    ; /* for-cycle skipped due to no free lvals variables */
    {
      cl::sycl::cl_double a1_zm[192];
      
      cl::sycl::cl_uchar v_r = 15 && 81;
      
      v_r += 18 + 60 + 79;
      ; /* for-cycle skipped due to nesting limit */
      if (v_r) {
        cl::sycl::cl_double a1_d[192];
        
        long v_j = 67 - (v_r? (31) % v_r : (67));
        
        v_j -= 58;
        v_j = 71;
        v_j *= 27 != v_j - 2;
        v_j += 1 + (+ 93, 57) + 81;
        return v_j;
      }
      return copy(v_r);
    }
    return (rval ERROR!!!);
  }
  ; /* lvalue change could be here */
  ; /* lvalue change could be here */
  return 45.59;
}
cl::sycl::cl_half f2_fum(cl::sycl::cl_float v_y, float v_v) {
  double a1_zvfnv[192];
  cl::sycl::cl_float a1_b[192];
  
  cl::sycl::cl_uchar v_elb = + 69;
  cl::sycl::cl_double v_ce = 40.6;
  cl::sycl::cl_char v_c = + 53;
  int v_c = 19;
  
  v_ce += (cast<long long>(v_ce)? (21.20 + v_c + ((v_v) ? v_v * 50.62 : 40.83) + 26.70) % cast<long long>(v_ce) : (96.89)) + 77.81 + 52.62;
  v_elb = 45;
  v_v = 90;
  return 56.79;
}
cl::sycl::cl_char f1_wkrb(int v_c) {
  
  double v_dnthnn = 92.27;
  unsigned int v_g = 64;
  
  v_dnthnn -= 94.88 * 8.65;
  v_c = v_dnthnn;
  if (cast<long long>(v_c)) {
    
    
    ; /* for-cycle skipped due to nesting limit */
    v_g *= 72;
    v_g -= cast<unsigned int>(v_dnthnn);
    return 12 + cast<cl::sycl::cl_char>(v_dnthnn);
  }
  v_c = v_c;
  v_g *= 42;
  return 91;
}
cl::sycl::cl_half f3_q(int v_rd, cl::sycl::cl_uchar v_m, cl::sycl::cl_char v_vwppi) {
  
  
  v_vwppi = 4;
  v_m = 41.78;
  ; /* for-cycle skipped due to nesting limit */
  v_rd *= v_vwppi;
  return v_m;
}

