#ifndef _SYCLSMITH_KERNEL_
#define _SYCLSMITH_KERNEL_
#include <CL/sycl.hpp>
template <typename T, int dims, cl::sycl::access::mode mode,
          cl::sycl::access::target target, cl::sycl::access::placeholder placeholder>
void kernel(cl::sycl::nd_item<dims> item, cl::sycl::accessor<T, dims, mode, target, placeholder> result);
#include "kernel_impl.hpp"
#endif
