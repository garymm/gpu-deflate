#include "kernel.h"

#include <cstdio>

#define CUDA_CHECK(expr)                                                \
  do {                                                                  \
    cudaError_t err = (expr);                                           \
    if (err != cudaSuccess) {                                           \
      fprintf(stderr, "CUDA Error Code : %d\n     Error String: %s\n", \
              err, cudaGetErrorString(err));                            \
      exit(err);                                                        \
    }                                                                   \
  } while (0)

__global__ void kernel() {
  printf("cuda kernel called!\n");
}

void launch() {
  int driver_version;
  CUDA_CHECK(cudaDriverGetVersion(&driver_version));
  printf("CUDA driver version: %d\n", driver_version);
  kernel<<<1, 1>>>();
  CUDA_CHECK(cudaGetLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
}
