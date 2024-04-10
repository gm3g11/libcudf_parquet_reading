#!/bin/bash

cmake -S . -B build/ -DCMAKE_CUDA_ARCHITECTURES=70 -DCMAKE_CXX_STANDARD=17 -Dcudf_ROOT=/home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/build 
#-DCUDF_USE_PER_THREAD_DEFAULT_STREAM=ON
cmake --build build/ --parallel 16
./build/basic_example
