# Copyright (c) 2020-2023, NVIDIA CORPORATION.

cmake_minimum_required(VERSION 3.26.4)

project(
  chunked_parquet_read
  VERSION 0.0.1
  LANGUAGES CXX CUDA
)

include(../../fetch_dependencies.cmake)

# Configure your project here
add_executable(chunked_parquet_read chunked_parquet_read_self_implementation.cpp)
target_link_libraries(chunked_parquet_read PRIVATE cudf::cudf)
target_compile_features(chunked_parquet_read PRIVATE cxx_std_17)
