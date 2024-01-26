#include <iostream>
#include <sycl/sycl.hpp>

template <class T>
struct IsVecNot : std::false_type
{};

template <typename T, int N>
struct IsVecNot<sycl::vec<T, N>> : std::true_type {};

template <typename T>
using EnableIfNotVecTypes = typename std::enable_if<!IsVecNot<T>::value, T>::type;
template <typename T>
using EnableIfVecTypes = typename std::enable_if<IsVecNot<T>::value, T>::type;

// Scalar n1 -> Scalar n2: n2=n1
template <typename T1, typename T2>
EnableIfNotVecTypes<T1> cast(T2 val) {
    return static_cast<T1>(val);
}

//Scalar n -> Vector v: v=(n,n,n...)
template <typename T1, typename T2, typename=EnableIfNotVecTypes<T2>>
EnableIfVecTypes<T1> cast(T2 val) {
    return T1(val);
}

// Vector -> Scalar
// Vector -> Vector
template <typename T1, typename T, int N> T1 cast(sycl::vec<T, N> vec) {
    return  T1(vec.s0());
}
