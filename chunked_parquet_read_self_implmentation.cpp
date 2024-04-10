#include <cudf/io/parquet.hpp>
#include <rmm/cuda_stream_view.hpp>
#include <rmm/mr/device/cuda_memory_resource.hpp>
#include <rmm/mr/device/per_device_resource.hpp>
#include <chrono>
#include <iostream>
#include <vector>

int main() {
    // const std::string file_path = "/mnt/ramfs/part-00198-tid-3747487300473043810-11eb4400-583b-4bd3-9c6c-a9803c7aeb94-3334-1-c000.snappy.parquet";
    const std::string file_path = "../dataset/output_no_compression.parquet";
    constexpr int32_t total_rows = 240578;
    constexpr int32_t chunked_read_num_chunks = 4;
    const int32_t chunk_row_cnt = total_rows / chunked_read_num_chunks;

    // Initialize CUDA memory resource
    rmm::mr::cuda_memory_resource cuda_mr;
    rmm::mr::set_current_device_resource(&cuda_mr);

    std::vector<rmm::cuda_stream> streams(chunked_read_num_chunks);
    cudf::size_type total_rows_read = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int32_t chunk = 0; chunk < chunked_read_num_chunks; ++chunk) {
        // streams[chunk] = rmm::cuda_stream();

        cudf::io::parquet_reader_options read_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path))
                                                            .skip_rows(chunk * chunk_row_cnt)
                                                            .num_rows((chunk == chunked_read_num_chunks - 1) ? (total_rows - chunk * chunk_row_cnt) : chunk_row_cnt)
                                                            .build();

        auto result = cudf::io::read_parquet(read_options, cudf::get_default_stream());
        total_rows_read += result.tbl->num_rows();
    }

    // Synchronize all streams
    // for (auto& stream : streams) {
    //     stream.synchronize();
    // }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Total rows read: " << total_rows_read << std::endl;
    std::cout << "Total read time: " << duration << " ms" << std::endl;

    return 0;
}