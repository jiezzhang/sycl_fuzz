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
#include <CL/sycl.hpp>


int f1_nak(cl::sycl::cl_uchar);
float f1_o(unsigned int);
cl::sycl::cl_char f1_tm(unsigned int);
cl::sycl::cl_float f1_hscw(cl::sycl::cl_double);
cl::sycl::cl_half f1_kzfsrhztxjv(cl::sycl::cl_char);

template <typename T, int dims, cl::sycl::access::mode mode,
        cl::sycl::access::target target, cl::sycl::access::placeholder placeholder>
void kernel(cl::sycl::nd_item<dims> item, cl::sycl::accessor<T, dims, mode, target, placeholder> result)
{
  cl::sycl::cl_float v_wbenps = result[item.get_global_linear_id()] + 95.93;
  unsigned char v_avgsoqx = 13;
  cl::sycl::cl_half v_wns = 75.1;
  cl::sycl::cl_float v_z = 49.66;
  
  v_wns += 100.42;
  ; /* for-cycle skipped due to nesting limit */
  v_avgsoqx += result[item.get_global_linear_id()];
}
int f1_nak(cl::sycl::cl_uchar v_i) {
  cl::sycl::cl_uchar a1_dx[192];
  cl::sycl::cl_float a1_a[192];
  
  int v_b = 2;
  long v_df = v_i;
  cl::sycl::cl_uint v_tu = 61;
  
  v_tu = f1_hscw(v_df);
  v_tu -= v_df + 55;
  ++v_i;
  return 63;
}
float f1_o(unsigned int v_d) {
  float a1_rpwtw[192];
  
  double v_fr = 15.77 + 67.79;
  
  v_fr = v_d - 84.48 * 94.57;
  v_d = f1_kzfsrhztxjv(f1_tm(static_cast<unsigned int>(v_fr) || 6)) + f1_hscw(f1_hscw(58.14)) + 12 + f1_hscw(61.41);
  v_d *= static_cast<cl::sycl::cl_uchar>(v_fr);
  return f1_hscw(51.91);
}
cl::sycl::cl_char f1_tm(unsigned int v_z) {
  cl::sycl::cl_half a1_s[192];
  
  float v_kdixsgs = 9.51;
  cl::sycl::cl_float v_gaxd = v_z + v_z;
  cl::sycl::cl_half v_wxo = v_gaxd;
  
  v_z = f1_kzfsrhztxjv(56 + f1_hscw(45.96));
  ; /* for-cycle skipped due to nesting limit */
  v_kdixsgs *= v_kdixsgs;
  return static_cast<cl::sycl::cl_char>(v_gaxd);
}
cl::sycl::cl_float f1_hscw(cl::sycl::cl_double v_byklo) {
  cl::sycl::cl_double a1_zng[192];
  
  
  ; /* for-cycle skipped due to nesting limit */
  v_byklo++;
  v_byklo *= 91.3 - f1_kzfsrhztxjv((86, f1_kzfsrhztxjv(static_cast<cl::sycl::cl_char>(v_byklo) + 44) + ((static_cast<cl::sycl::cl_char>(v_byklo), f1_kzfsrhztxjv(static_cast<cl::sycl::cl_char>(v_byklo))))));
  return 47.23;
}
cl::sycl::cl_half f1_kzfsrhztxjv(cl::sycl::cl_char v_sm) {
  
  unsigned short v_m = 57;
  
  v_m += v_m;
  v_sm = v_m;
  switch (static_cast<size_t>(v_m * v_m + static_cast<int>(v_sm))) {
    case 95: 
      v_sm = v_sm;
      v_m = 50;    
    case 63: 
      v_sm = 6.86;    
    case 44: 
      v_m += 11 + 7;
      v_m = ~ 6;    
    
    default: 
      v_sm *= 5.63;
  }
  v_m += 52;
  v_sm = 21.98 + 94.40;
  return v_sm;
}

