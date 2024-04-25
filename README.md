# libcudf Parquet Reading Optimization

This repository contains efforts to optimize the Parquet file reading capabilities of `libcudf`. We explore various optimizations including memory management, multi-streaming, and multi-threading techniques to enhance performance.

## Getting Started

### Prerequisites

- CMake
- CUDA environment
- libcudf and libarrow libraries

You could refer this link to install libcudf: https://github.com/rapidsai/cudf

And refer this link to install libarrow:https://arrow.apache.org/install/

I have also summarized my installation steps, along with the issues I encountered and their solutions, in the Libcudf_compile.md file. I hope this document will help make your compilation successful.

### Building the Project

1. Clone the repository:   
   git clone https://github.com/gm3g11/libcudf_parquet_reading.git
2. Navigate to the project directory:
   cd /xxx_dir/libcudf_parquet_reading
3. Modify the CMakeLists.txt
   
   Configure your project with different project name and cuda file.
   E.g., in this CMakeLists.txt, we are using "basic_example" (line 6) as a project name and compile "chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp" (line 14)
4. Compile and runtime command in build.sh:
   bash build.sh

   Explain:
   
   A. Pre-compile command: cmake -S . -B build/ -DCMAKE_CUDA_ARCHITECTURES=70 -DCMAKE_CXX_STANDARD=17 -Dcudf_ROOT=/home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/build
   
   B. Compile command: cmake --build build/ --parallel 16
   
   C. Runtime command: ./build/basic_example
   
   (Need to modify these commands depending on your cases.)
### Usage
1. lib_arrow.cpp: The benchmark method derived from Apache Arrow.
   Compile command: g++ -O3 -fopenmp -o arrow_parquet -std=c++17 lib_arrow.cpp  -lparquet -larrow -lgomp
   Runtime command: ./arrow_parquet your_parquet_file
2. parquet_read_baseline.cpp: The benchmark method for libcudf

   (You can modify this file with different settings, including: pool_memory, ramfs)
3. chunked_parquet_read_self_implmentation.cpp: chunked parquet read
4. chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp: chunked parquet read + streams + threads 

### Contact
For questions or support, please open an issue in the GitHub repository or directly drop me an e-mail: gmeng@nd.edu.
