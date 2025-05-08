#include<iostream>
#include <cuda_runtime.h>
#include<cuda.h>
#include<device_launch_parameters.h>

__global__ void addVectors(int *a, int *b, int *c, int n) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n) {
        c[index] = a[index] + b[index];
    }
}

int main(){
    int n = 1000000;
    int size = n*sizeof(int);

    // Host memory allocation
    int *h_a = new int[n];
    int *h_b = new int[n];
    int *h_c = new int[n];

    // Device memory pointers
    int *d_a, *d_b, *d_c;

    // Initialize host arrays
    for(int i = 0; i < n; i++) {
        h_a[i] = i;
        h_b[i] = i*2;
    }

    // Allocate device memory
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    // Copy data from host to device
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (n + blockSize - 1) / blockSize;
    addVectors<<<numBlocks, blockSize>>>(d_a, d_b, d_c, n);

    // Copy result back to host
    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    // Print first few elements
    for(int i = 0; i < 10; i++) {
        std::cout << h_c[i] << " ";
    }
    std::cout << "...\n";

    // Free device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    // Free host memory
    delete[] h_a;
    delete[] h_b;
    delete[] h_c;

    return 0;
}



