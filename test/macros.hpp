#ifndef _MACROS_H_
#define _MACROS_H_

#include <sycl/sycl.hpp>
using namespace sycl;

#define MAKE_VEC(t1, t2)                                                       \
  using t1 = t2;                                                               \
  using t1##2 = t2##2;                                                         \
  using t1##3 = t2##3;                                                         \
  using t1##4 = t2##4;                                                         \
  using t1##8 = t2##8;                                                         \
  using t1##16 = t2##16;

#ifdef NON_DOUBLE
MAKE_VEC(DOUBLE, float);
#else
MAKE_VEC(DOUBLE, double);
#endif

#ifdef NON_HALF
MAKE_VEC(HALF, float);
#else
MAKE_VEC(HALF, half);
#endif

#endif