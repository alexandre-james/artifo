#include "convolution.hpp"
#include "../image/gray_image.hpp"
#include "../image/rgb_image.hpp"
#include "../image/rgba_image.hpp"
#include "../image/hsv_image.hpp"

#include <cstdio>

#define gpu_check(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

__device__ uint8_t device_bound(int nb) {
    if (nb > MAX_LEVEL)
        return MAX_LEVEL;
    if (nb < 0)
        return 0;
    return nb;
}

__global__ void convolve_pixel(uint8_t *output, uint8_t *input, float *kernel,
    int input_width, int input_height, int kernel_width, int kernel_height) {

    int y = threadIdx.y + blockIdx.y * blockDim.y;
    int x = threadIdx.x + blockIdx.x * blockDim.x;

    if (y >= input_height || x >= input_width)
        return;

    float sum = 0;

    for (int i = 0; i < kernel_height; i++) {
        for (int j = 0; j < kernel_width; j++) {
            int y_pos = y - kernel_height / 2 + i;
            int x_pos = x - kernel_width / 2 + j;
            uint8_t value = 0;
            if (x_pos >= 0 && y_pos >= 0 && y_pos < input_height && x_pos < input_width)
                value = input[y_pos * input_width + x_pos];
            sum += (float) kernel[i * kernel_width + j] * value;
        }
    }
    output[y * input_width + x] = device_bound(sum);
}

template <typename image_type>
image_type *convolve(image_type *input, mask *kernel) {
    int tx = 24;
    int ty = 16;

    dim3 blocks(input->width * input->dim / tx + 1, input->height / ty + 1);
    dim3 threads(tx, ty);

    uint8_t *output_gpu;
    uint8_t *input_gpu;
    float *kernel_gpu;

    cudaMalloc((void **) &output_gpu, input->length * sizeof(uint8_t));
    gpu_check(cudaGetLastError());

    cudaMalloc((void **) &input_gpu, input->length * sizeof(uint8_t));
    gpu_check(cudaGetLastError());

    cudaMalloc((void **) &kernel_gpu, kernel->width * kernel->height * sizeof(float));
    gpu_check(cudaGetLastError());

    cudaMemcpy(input_gpu, input->pixels, input->length * sizeof(uint8_t), cudaMemcpyHostToDevice);
    gpu_check(cudaGetLastError());

    cudaMemcpy(kernel_gpu, kernel->values, kernel->width * kernel->height * sizeof(float), cudaMemcpyHostToDevice);
    gpu_check(cudaGetLastError());
    
    convolve_pixel<<<blocks, threads>>>(output_gpu, input_gpu, kernel_gpu,
    input->width * input->dim, input->height, kernel->width, kernel->height);
    gpu_check(cudaGetLastError());
    gpu_check(cudaDeviceSynchronize());

    image_type *output = new image_type(input->width, input->height);
    cudaMemcpy(output->pixels, output_gpu, output->length * sizeof(uint8_t), cudaMemcpyDeviceToHost);

    cudaFree(output_gpu);
    cudaFree(input_gpu);
    cudaFree(kernel_gpu);

    return output;
}

template gray_image *convolve(gray_image *, mask *);
template rgb_image *convolve(rgb_image *, mask *);
template rgba_image *convolve(rgba_image *, mask *);
template hsv_image *convolve(hsv_image *, mask *);