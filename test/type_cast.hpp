#include <iostream>
#include <CL/sycl.hpp>

template <class T>
struct IsVecNot : std::false_type
{};

template <typename T, int N>
struct IsVecNot<cl::sycl::vec<T, N>> : std::true_type
{};

template <typename T>
using EnableIfNotVecTypes = typename std::enable_if<!IsVecNot<T>::value, T>::type;
template <typename T>
using EnableIfVecTypes = typename std::enable_if<IsVecNot<T>::value, T>::type;

template <typename T1, typename T, int N>
EnableIfNotVecTypes<T1> cast(cl::sycl::vec<T, N> vec) {
    return  T1(vec.x());
}

template <typename T1, typename T2>
EnableIfNotVecTypes<T1> cast(T2 val) {
    return static_cast<T1>(val);
}

template <typename T1,typename T2, int N>
EnableIfVecTypes<T1> cast(cl::sycl::vec<T2, N> vec) {
    return vec.template convert<typename T1::element_type>();
}

template <typename T1, typename T2, typename=EnableIfNotVecTypes<T2>>
EnableIfVecTypes<T1> cast(T2 val) {
    return T1(val);
}

