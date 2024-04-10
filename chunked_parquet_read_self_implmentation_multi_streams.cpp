#include <cudf/io/parquet.hpp>
#include <rmm/cuda_stream_view.hpp>
#include <rmm/mr/device/cuda_memory_resource.hpp>
#include <rmm/mr/device/per_device_resource.hpp>
#include <chrono>
#include <iostream>
#include <vector>

int main() {
    const std::string file_path = "../dataset/output_no_compression.parquet";
    constexpr int32_t total_rows = 240578;
    constexpr int32_t num_streams = 4;  // Use 4 streams

    // Initialize CUDA memory resource
    rmm::mr::cuda_memory_resource cuda_mr;
    rmm::mr::set_current_device_resource(&cuda_mr);

    std::vector<rmm::cuda_stream> streams(num_streams);
    cudf::size_type total_rows_read = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Create and initialize streams
    for (int32_t i = 0; i < num_streams; ++i) {
        streams[i] = rmm::cuda_stream();
    }

    // Use only one stream for reading since there is only one chunk
    cudf::io::parquet_reader_options read_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path))
                                                        .build();

    auto result = cudf::io::read_parquet(read_options, streams[0]);  // Use the first stream
    total_rows_read += result.tbl->num_rows();

    // Synchronize all streams
    for (auto& stream : streams) {
        stream.synchronize();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Total rows read: " << total_rows_read << std::endl;
    std::cout << "Total read time: " << duration << " ms" << std::endl;

    return 0;
}
