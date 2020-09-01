#include "common.hpp"
#include "kernel.hpp"

int main(int argc, char **argv) {
  argument arg;
  if (!arg.parse(argc, argv)) {
    return 1;
  }
  std::string platform_name = arg.get_required_value("p");
  std::string device_name = arg.get_required_value("d");
  fuzz_selector selector(platform_name, device_name);

  const int dim = 1024;
  const int local_dim = 8;
  std::vector<ulong> result(dim);

  {
    cl::sycl::queue queue(selector);
    cl::sycl::range<1> global_range(dim);
    cl::sycl::range<1> local_range(local_dim);
    cl::sycl::buffer<ulong, 1> res_buffer(result.data(), global_range);

    kernel_fun(queue, global_range, local_range, res_buffer);
  }

  // Data verification
  ulong baseline = result[0];
  for (size_t i = 0; i < dim; ++i) {
    if (result[i] != baseline) {
      printf("Result mismatch in %zu: %lu vs %lu \n", i, result[i], baseline);
      return 255;
    }
  }
  std::cout << "Test pass!" << std::endl;

  return 0;
}