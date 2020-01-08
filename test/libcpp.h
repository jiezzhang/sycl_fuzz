#ifndef _LIBCPP_H_
#define _LIBCPP_H_
template <typename T1, typename T2> void swap(T1 &a, T2 &b) {
  T2 c = a;
  a = b;
  b = c;
}

template <typename T> T copy(T x) { return x; }
#endif