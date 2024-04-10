#include <cudf/io/parquet.hpp>
#include <cudf/table/table.hpp>
#include <rmm/cuda_stream_view.hpp>
#include <rmm/mr/device/cuda_memory_resource.hpp>
#include <rmm/mr/device/per_device_resource.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

void read_parquet_chunk(
    const std::string& file_path,
    int32_t chunk,
    int32_t chunk_row_cnt,
    int32_t total_rows,
    int32_t chunked_read_num_chunks,
    std::vector<std::unique_ptr<cudf::table>>& results,
    rmm::cuda_stream& stream) {
    cudf::io::parquet_reader_options read_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path))
    .skip_rows(chunk * chunk_row_cnt)
    .num_rows((chunk == chunked_read_num_chunks - 1) ? (total_rows - chunk * chunk_row_cnt) : chunk_row_cnt)
    .build();

    auto result = cudf::io::read_parquet(read_options, stream);
    results[chunk] = std::move(result.tbl);
}

int main() {
    // const std::string file_path = "./dataset/output_no_compression_8M.parquet";
    // constexpr int32_t total_rows = 8000000;
    // constexpr int32_t chunked_read_num_chunks = 4;
    const std::string file_path = "../dataset/output_no_compression.parquet";
    constexpr int32_t total_rows = 240578;
    constexpr int32_t chunked_read_num_chunks = 4;
    const int32_t chunk_row_cnt = total_rows / chunked_read_num_chunks;

    // Initialize CUDA memory resource
    rmm::mr::cuda_memory_resource cuda_mr;
    rmm::mr::set_current_device_resource(&cuda_mr);

    std::vector<rmm::cuda_stream> streams(chunked_read_num_chunks);
    std::vector<std::unique_ptr<cudf::table>> results(chunked_read_num_chunks);
    std::vector<std::thread> threads;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int32_t chunk = 0; chunk < chunked_read_num_chunks; ++chunk) {
        streams[chunk] = rmm::cuda_stream();
        threads.emplace_back(read_parquet_chunk, std::ref(file_path), chunk, chunk_row_cnt, total_rows,
                             chunked_read_num_chunks, std::ref(results), std::ref(streams[chunk]));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Synchronize all streams
    for (auto& stream : streams) {
        stream.synchronize();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    cudf::size_type total_rows_read = 0;
    for (const auto& result : results) {
        total_rows_read += result->num_rows();
    }
    std::cout << "Total rows read: " << total_rows_read << std::endl;
    std::cout << "Total read time: " << duration << " ms" << std::endl;

    return 0;
}
