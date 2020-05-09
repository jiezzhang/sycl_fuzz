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


cl::sycl::cl_uchar f1_he(cl::sycl::cl_float);
unsigned int f1_kbl(int);
float f1_qbdp(cl::sycl::cl_char);
int f1_tjyvl(unsigned short);
cl::sycl::cl_char f1_b(unsigned int);

template <typename T, int dims, cl::sycl::access::mode mode,
        cl::sycl::access::target target, cl::sycl::access::placeholder placeholder>
void kernel_fun(cl::sycl::nd_item<dims> item, cl::sycl::accessor<T, dims, mode, target, placeholder> result)
{
  unsigned int v_rk = 1 + + 27 + result[item.get_global_linear_id()];
  cl::sycl::cl_float v_ve = 82.18;
  
  result[item.get_global_linear_id()] *= v_rk;
  for (v_ve=62; v_ve <= 63; v_ve--) {
    
    int v_s = 31;
    
    if (v_rk) {
      
      cl::sycl::cl_half v_bqf = 73.23;
      cl::sycl::cl_double v_wscs = 46.30;
      double v_u = 3.76;
      int v_nm = 36;
      
      break;
      v_u -= 39.30;
      v_nm -= cast<int>(v_ve);
      
    }
    v_s = ~ v_rk;
    v_rk++;
    v_rk = 78 - result[item.get_global_linear_id()] + 83 * 20;
    
  }
  v_ve += result[item.get_global_linear_id()];
  for (result[item.get_global_linear_id()]=16; result[item.get_global_linear_id()] <= 63; result[item.get_global_linear_id()]++) {
    
    cl::sycl::cl_uchar v_l = 93;
    
    v_rk += 71 + cast<unsigned int>(v_ve);
    {
      float a1_d[192];
      unsigned int a1_dxohesrqj[192];
      
      
      v_l = 29 - 64 * 98;
      ++v_l;
      v_l = cast<cl::sycl::cl_uchar>(v_ve);
      ++v_l;
      v_rk += 70;
      
    }
    v_rk = 27 + 27;
    
  }
  result[item.get_global_linear_id()] -= 1;
  v_ve = 20.66;
  v_ve = v_ve;
}
cl::sycl::cl_uchar f1_he(cl::sycl::cl_float v_oenbac) {
  cl::sycl::cl_char a1_mrqjj[192];
  
  cl::sycl::cl_float v_y = 37.72;
  cl::sycl::cl_half v_b = 83.18;
  
  v_y += 18.80;
  v_b++;
  ++v_y;
  return 35;
}
unsigned int f1_kbl(int v_rmpneoj) {
  double a1_q[192];
  
  double v_rsfkxn = 27.84 + v_rmpneoj + v_rmpneoj;
  
  ++v_rmpneoj;
  v_rmpneoj = 82.34;
  for (v_rmpneoj=26; v_rmpneoj <= 34; v_rmpneoj++) {
    cl::sycl::cl_float a1_wtp[192];
    cl::sycl::cl_half a1_aze[192];
    
    cl::sycl::cl_float v_wvkbg = v_rmpneoj * 5.78;
    
    v_wvkbg -= 36.29;
    v_rsfkxn = 91.22 + 26.78;
    for (v_wvkbg=0; v_wvkbg <= 63; v_wvkbg++) {
      cl::sycl::cl_float a1_g[192];
      int a1_ak[192];
      
      
      v_rsfkxn += (20.97 * 51.54);
      v_rsfkxn -= (a1_aze[cast<size_t>(v_wvkbg+v_wvkbg)], 45.48);
      ++v_rsfkxn;
      return 60;
    }
    return 64;
  }
  return cast<unsigned int>(v_rmpneoj) - cast<unsigned int>(v_rsfkxn) + 66;
}
float f1_qbdp(cl::sycl::cl_char v_ss) {
  
  
  v_ss = v_ss;
  for (v_ss=28; v_ss <= 63; ++v_ss) {
    
    int v_obcg = 86;
    cl::sycl::cl_char v_lr = 53 + 97;
    unsigned int v_iglz = 95 + (- 65);
    
    for (v_iglz=v_ss; v_iglz <= v_ss; v_iglz++) {
      
      unsigned int v_bp = 94 + 5;
      
      for (v_bp=0; v_bp <= 45; v_bp++) {
        cl::sycl::cl_uchar a1_snfyc[192];
        
        unsigned int v_vo = v_lr;
        cl::sycl::cl_char v_ffm = 43;
        
        v_obcg = 31 + 49;
        v_vo = 78;
        v_vo -= 68;
        return 35.38 + v_ss + 65.59;
      }
      break;
      v_bp -= copy(v_obcg);
      return 82.92 + 10.26;
    }
    for (v_iglz=v_ss; v_iglz <= v_ss; v_iglz += 7) {
      int a1_yg[192];
      
      float v_hamuo = 78.87;
      float v_k = 29.35 + 18.83;
      unsigned int v_q = 61;
      cl::sycl::cl_half v_ll = v_iglz;
      
      if (cast<long long>(v_hamuo)) {
        cl::sycl::cl_half a1_crfx[192];
        unsigned int a1_kqe[192];
        
        float v_btq = v_lr + v_q;
        cl::sycl::cl_double v_rad = (v_iglz ? v_ss * 87.22 : 41.39);
        
        v_q -= cast<unsigned int>(v_ll);
        v_lr++;
        v_ll = (52 == 59 ? v_q : v_lr - ((copy(v_iglz) ? 72 : v_ss * 82 + copy(cast<long>(v_ll))) < cast<long>(v_rad) ? (48.16) : 67.49 + (a1_crfx[cast<size_t>(v_ss+114)] ? 33.65 * v_rad : 8.67)));
        return 8.61;
      } else {
        cl::sycl::cl_char a1_ghgt[192];
        cl::sycl::cl_double a1_csma[192];
        
        cl::sycl::cl_float v_l = 19.94;
        int v_zidi = 87;
        
        v_l *= 94.18;
        for (v_obcg=v_iglz; v_obcg > 0; v_obcg--) {
          double a1_qocj[192];
          int a1_sksk[192];
          
          double v_d = v_hamuo;
          float v_xojtefjvs = v_q;
          cl::sycl::cl_float v_wq = 89.95;
          
          v_hamuo += 64.60;
          v_ll = a1_qocj[cast<size_t>(v_ss)];
          v_q = 24;
          v_xojtefjvs += (a1_csma[cast<size_t>(((unsigned int)(a1_yg[cast<size_t>(v_ss)]))%192)], 27.58);
          return 16.90;
        }
        v_l = v_q;
        return v_q;
      }
      v_obcg *= 91;
      v_k *= 6.57;
      return v_lr;
    }
    v_iglz *= 3;
    return v_iglz;
  }
  v_ss = v_ss;
  return v_ss;
}
int f1_tjyvl(unsigned short v_vtba) {
  
  double v_pxcvvf = 96.37;
  
  for (v_vtba=19; v_vtba <= 63; ++v_vtba) {
    double a1_t[192];
    
    cl::sycl::cl_uchar v_xkpctktd = ((37, 69) != v_vtba + 25 - v_vtba ? (v_vtba, 66) : 85 - v_vtba);
    cl::sycl::cl_double v_rs = v_xkpctktd;
    cl::sycl::cl_uchar v_c = v_xkpctktd;
    
    if (v_c) {
      cl::sycl::cl_half a1_elsh[192];
      cl::sycl::cl_half a1_n[192];
      
      short v_xb = v_vtba + 92;
      
      v_rs++;
      v_pxcvvf = 82.56;
      v_rs = 78.30;
      v_rs -= 54.26 + 100.72;
      v_pxcvvf = v_pxcvvf;
      v_xkpctktd++;
      v_rs *= v_rs;
      return 52;
    }
    v_pxcvvf = v_vtba;
    v_pxcvvf = a1_t[cast<size_t>(v_vtba)] - 56.56 * 64.15;
    return a1_t[cast<size_t>(v_vtba)];
  }
  for (v_pxcvvf=16; v_pxcvvf <= 63; ++v_pxcvvf) {
    
    unsigned int v_xcg = 38 + 73;
    float v_sk = v_xcg;
    
    ++v_xcg;
    v_sk = v_sk;
    switch (cast<size_t>(31)) {
      case 93: 
        v_sk += 83.35 + 39.46;
        break;      
      case 82: 
        {
          
          cl::sycl::cl_half v_vymo = 87.5;
          
          if (cast<long long>(v_pxcvvf)) {
            int a1_pgru[192];
            
            cl::sycl::cl_double v_n = (37.91 + v_vtba);
            cl::sycl::cl_float v_qotr = 55.11;
            
            if (cast<long long>(v_pxcvvf)) {
              cl::sycl::cl_char a1_q[192];
              
              float v_bb = 14.89;
              
              v_vymo = v_pxcvvf + 2.36;
              {
                
                cl::sycl::cl_uchar v_lq = 36;
                double v_qb = 64.99;
                
                v_qb = v_vtba + a1_pgru[cast<size_t>(v_pxcvvf)];
                v_qb++;
                v_qb = v_pxcvvf;
                switch (cast<size_t>(62)) {
                  case 70: 
                    v_lq -= 44;
                    break;                  
                  case 72: 
                    switch (cast<size_t>((cast<long long>(v_qotr) ? 46 - (3) + 31 : (100 - v_vtba, 28 * 23)))) {
                      case 42: 
                        {
                          cl::sycl::cl_char a1_u[192];
                          
                          
                          v_lq = 91;
                          for (v_n=20; v_n <= 57; v_n += 3) {
                            int a1_imk[192];
                            
                            
                            v_qb += v_bb * 78.7;
                            v_qotr *= 43.13 - 96.56;
                            for (v_qotr=v_n; v_qotr <= 63; ++v_qotr) {
                              double a1_z[192];
                              double a1_k[192];
                              
                              int v_f = v_xcg;
                              unsigned int v_ky = 2;
                              
                              v_ky = 75 + 26;
                              ++v_lq;
                              v_qb++;
                              v_sk *= 23.51;
                              ; /* for-cycle skipped due to nesting limit */
                              v_vymo += v_f;
                              ++v_bb;
                              return cast<int>(v_vymo);
                            }
                            return 35;
                          }
                          v_vtba = 45;
                          return cast<int>(v_n) + 83 - 90;
                        }                      
                      case 67: 
                        for (v_lq=50; v_lq <= 63; v_lq--) {
                          double a1_g[192];
                          unsigned int a1_igw[192];
                          
                          int v_xl = 85 * 61;
                          cl::sycl::cl_double v_qf = (80.10);
                          int v_pfdkten = 25;
                          
                          {
                            cl::sycl::cl_double a1_ni[192];
                            
                            cl::sycl::cl_uchar v_qrtxg = 70;
                            
                            v_xcg *= 41;
                            v_xcg = 53;
                            v_qf *= v_n;
                            if (cast<long long>(v_qotr)) {
                              
                              
                              v_bb -= v_n + 78.18;
                              v_qb -= 54.38;
                              for (v_n=v_lq; v_n <= 47; v_n++) {
                                cl::sycl::cl_float a1_b[192];
                                int a1_p[192];
                                
                                int v_qivv = 25;
                                double v_ddlph = v_xl + 78.64;
                                
                                v_bb = 15.92 + v_xl;
                                v_ddlph *= 46.97 * ((v_lq? (76.52) / v_lq : ((v_qrtxg ? v_sk : 77.98) - 77.81)), 35.18);
                                v_qb *= 93.78;
                                v_xl = v_qivv;
                                v_pfdkten = 96;
                                return 21;
                              }
                              return cast<int>(v_n);
                            }
                            v_qotr = 94.97 * 42.77;
                            return 61 + 13 + 100;
                          }
                          for (v_qf=0; v_qf <= v_lq; ++v_qf) {
                            cl::sycl::cl_double a1_c[192];
                            
                            cl::sycl::cl_double v_jo = 46.27;
                            cl::sycl::cl_uchar v_bbrzhzvtot = 85;
                            cl::sycl::cl_float v_p = v_jo;
                            cl::sycl::cl_double v_o = 67.82;
                            
                            if (a1_g[cast<size_t>(((unsigned int)(16 + 47))%192)]) {
                              
                              cl::sycl::cl_char v_ifx = 62;
                              cl::sycl::cl_char v_zzaubjy = cast<cl::sycl::cl_char>(v_qb);
                              double v_fl = v_qb;
                              long long v_sbsz = 31;
                              
                              ++v_xl;
                              v_o -= 41.51;
                              v_vymo++;
                              v_xl -= v_sbsz;
                              return cast<int>(v_qf);
                            }
                            v_bb -= 73.34;
                            v_bb = v_pfdkten;
                            return 78 - 83 + cast<int>(v_qb);
                          }
                          v_xcg -= 28;
                          return v_pfdkten;
                        }
                        for (v_n=v_pxcvvf; v_n <= 45; ++v_n) {
                          cl::sycl::cl_uchar a1_vzgbklnj[192];
                          long long a1_sh[192];
                          
                          cl::sycl::cl_float v_jebaf = 65.62;
                          
                          v_qotr *= v_jebaf - 22.72;
                          v_xcg += a1_vzgbklnj[cast<size_t>(v_pxcvvf)];
                          if (cast<long long>(v_sk)) {
                            
                            double v_d = 39.16 + 56.79;
                            double v_p = v_n;
                            
                            v_bb *= 42.7;
                            v_xcg *= v_lq + 85 * a1_vzgbklnj[cast<size_t>(v_n+v_pxcvvf)];
                            v_jebaf++;
                            return 83;
                          } else {
                            cl::sycl::cl_half a1_zzvpgqtta[192];
                            
                            cl::sycl::cl_float v_cn = 99.60;
                            cl::sycl::cl_double v_avvyq = 6.26;
                            
                            for (v_jebaf=v_pxcvvf; v_jebaf <= 32; v_jebaf += 3) {
                              
                              cl::sycl::cl_double v_qcdyl = v_pxcvvf;
                              
                              v_cn *= v_qb;
                              v_vymo += v_pxcvvf;
                              v_vtba += 58;
                              return (cast<int>(v_n)? ((71, 8 + 57) + cast<int>(v_qotr)) / cast<int>(v_n) : (48));
                            }
                            if (a1_q[cast<size_t>(v_pxcvvf)]) {
                              unsigned int a1_cionc[192];
                              
                              
                              v_cn -= 27.15;
                              v_sk = v_vymo;
                              v_cn -= 95.76;
                              ++v_vtba;
                              return 73;
                            }
                            {
                              cl::sycl::cl_float a1_u[192];
                              double a1_c[192];
                              
                              int v_wfs = 2 + 18;
                              unsigned long v_k = 90;
                              float v_lbuvkkjz = v_xcg;
                              
                              {
                                cl::sycl::cl_half a1_jodv[192];
                                
                                cl::sycl::cl_float v_lmxhdjzbu = 83.5 + 79.8;
                                
                                v_wfs -= 18;
                                v_k *= cast<unsigned long>(v_cn);
                                {
                                  
                                  cl::sycl::cl_half v_nhv = 86.97;
                                  double v_di = 42.32;
                                  cl::sycl::cl_float v_j = 53.38 * (v_pxcvvf + 77.22, (74.64 + 64.24));
                                  
                                  v_nhv = 88.53;
                                  v_qotr += 39.25 + 61.67 - (cast<long long>(v_bb) ? 53.13 + 41.3 : v_avvyq + v_di);
                                  v_sk *= a1_zzvpgqtta[cast<size_t>(v_n)];
                                  return 15;
                                }
                                v_avvyq *= v_sk;
                                return 96;
                              }
                              v_lq = 10 * 28;
                              v_avvyq -= 96.59 + 18.10;
                              return 29;
                            }
                            return 42;
                          }
                          return (- 14 - 40, 59);
                        }
                        v_xcg += 55 + 88;                      
                      case 21: 
                        v_sk -= 23.13 + 74.11;                      
                      case 90: 
                        for (v_qb=0; v_qb <= 58; ++v_qb) {
                          
                          cl::sycl::cl_float v_e = 29.20;
                          
                          v_e -= 74.88;
                          break;
                          v_lq += cast<cl::sycl::cl_uchar>(v_e) - cast<cl::sycl::cl_uchar>(v_n);
                          v_vtba = cast<unsigned int>(v_pxcvvf);
                          v_n = 25.58;
                          return 9;
                        }
                        break;                      
                      case 97: 
                        for (v_lq=61; v_lq > v_pxcvvf; v_lq--) {
                          
                          unsigned int v_twtt = 20 * 61;
                          double v_k = 95.46 + 85.65;
                          
                          v_sk += 63.80;
                          v_qb = 46.20;
                          v_n -= a1_pgru[cast<size_t>(((unsigned int)(54))%192)];
                          {
                            cl::sycl::cl_char a1_nta[192];
                            long long a1_mx[192];
                            
                            
                            v_sk += 39.61;
                            v_n *= v_lq;
                            v_bb -= 69.44;
                            return 32;
                          }
                          return 16 * 39;
                        }
                        {
                          
                          
                          ++v_lq;
                          v_vtba += 44;
                          switch (cast<size_t>(98 + 22)) {
                            case 56: 
                              v_vymo -= 70.47;                            
                            case 65: 
                              v_n = v_xcg + 49.20;
                              ++v_qb;
                              for (v_vtba=v_pxcvvf; v_vtba <= 50; v_vtba += 6) {
                                cl::sycl::cl_double a1_kn[192];
                                
                                double v_ltzxkenlm = 30.48;
                                
                                v_vymo -= 45.60;
                                v_n *= 78.17;
                                v_qotr = 91.47 * v_bb;
                                return 67 + 85;
                              }
                              break;                            
                            case 84: 
                              if (v_lq || cast<long long>(v_n)) {
                                
                                cl::sycl::cl_uchar v_lg = v_lq;
                                
                                v_qb *= 63.55;
                                {
                                  cl::sycl::cl_double a1_c[192];
                                  float a1_xy[192];
                                  
                                  int v_kowiz = 77 * (69 + + 1) + 11;
                                  cl::sycl::cl_double v_yfwr = 74.54 - 66.42 + 100.24 - v_lg + 82.56;
                                  cl::sycl::cl_float v_v = (11.92);
                                  unsigned int v_vq = v_lg;
                                  
                                  for (v_vymo=14; v_vymo <= 57; v_vymo++) {
                                    cl::sycl::cl_uchar a1_xej[192];
                                    long a1_w[192];
                                    
                                    int v_t = 20;
                                    
                                    v_yfwr *= 26.38 * v_vq + 43.76;
                                    ++v_sk;
                                    v_v = v_v;
                                    return 26;
                                  }
                                  v_lg++;
                                  v_vtba = 30;
                                  return 37;
                                }
                                v_bb *= 30.11;
                                v_sk = 12.17 * 63.67;
                                return 75;
                              } else {
                                cl::sycl::cl_uchar a1_uisoc[192];
                                
                                char v_f = cast<char>(v_qotr);
                                float v_uw = 25.23;
                                unsigned int v_ng = + 64 * v_vtba;
                                int v_tkr = (cast<long long>(v_vymo) ? 41 : 36);
                                
                                if ((cast<long long>(v_sk))) {
                                  
                                  cl::sycl::cl_half v_ewv = v_lq;
                                  cl::sycl::cl_float v_rvphgjs = 42.26 + 24.47;
                                  
                                  v_xcg++;
                                  v_sk += 45.73;
                                  v_n = 19.57;
                                  return 4;
                                } else {
                                  int a1_5[192];
                                  
                                  int v_13 = 42;
                                  
                                  v_13 = 18;
                                  v_uw = 13.27;
                                  v_sk = 38.30;
                                  return 8;
                                }
                                v_vtba = 10;
                                v_uw = 65.31;
                                return 3;
                              }
                              v_vymo = 17.23;
                              break;                            
                            case 96: 
                              v_qotr = 67.100;                            
                            
                            default: 
                              v_xcg = 92;
                          }
                          v_qotr = 71.31;
                          return 76;
                        }                      
                      
                      default: 
                        v_qotr = 74.98;
                    }
                    v_qb = 49.61;
                    break;                  
                  case 21: 
                    v_qotr = 10.63;                  
                  case 74: 
                    v_vtba = 69;                  
                  
                  default: 
                    v_vymo = 87.74;
                }
                v_qotr = 8.100;
                return 55;
              }
              v_vymo = 9.79;
              return 26;
            } else {
              int a1_53[192];
              int a1_25[192];
              
              int v_38 = 21;
              int v_3 = 52;
              int v_94 = 53;
              int v_39 = 38;
              
              v_3 = 28;
              v_xcg = 36;
              v_vymo = 72.69;
              return 97;
            }
            v_sk = 75.58;
            v_vtba = 100;
            return 84;
          }
          v_vtba = 32;
          v_sk = 52.15;
          return 81;
        }
        v_sk = 67.36;      
      case 59: 
        v_sk = 3.97;      
      case 94: 
        v_vtba = 80;      
      
    }
    return 55;
  }
  v_pxcvvf = 100.42;
  return 80;
}
cl::sycl::cl_char f1_b(unsigned int v_37) {
  int a1_10[192];
  int a1_73[192];
  
  int v_67 = 94;
  int v_50 = 14;
  
  v_67 = 77;
  v_50 = 30;
  v_67 = 84;
  return 7;
}

