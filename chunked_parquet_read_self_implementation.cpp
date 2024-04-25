#include <cudf/io/parquet.hpp>
#include <rmm/mr/device/cuda_memory_resource.hpp>
#include <rmm/mr/device/device_memory_resource.hpp>
#include <rmm/mr/device/pool_memory_resource.hpp>
#include <chrono>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file_path> <num_chunks>" << std::endl;
        return 1;
    }
    
    const std::string file_path = argv[1];
    const int32_t chunked_read_num_chunks = std::stoi(argv[2]);
    
    // Initialize CUDA memory resource
    rmm::mr::cuda_memory_resource cuda_mr{};
    rmm::mr::pool_memory_resource<rmm::mr::cuda_memory_resource> mr{&cuda_mr, rmm::percent_of_free_device_memory(80)};
    rmm::mr::set_current_device_resource(&mr);
    
    // Read the entire file to determine total number of rows
    auto total_row_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path)).build();
    auto total_row_table = cudf::io::read_parquet(total_row_options);
    const int32_t total_rows = total_row_table.tbl->num_rows();

    cudf::size_type total_rows_read = 0;
    int32_t chunk_row_cnt = total_rows / chunked_read_num_chunks;
    
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int32_t chunk = 0; chunk < chunked_read_num_chunks; ++chunk) {
        int32_t rows_to_read = (chunk == chunked_read_num_chunks - 1) ? (total_rows - chunk * chunk_row_cnt) : chunk_row_cnt;

        cudf::io::parquet_reader_options read_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path))
                                                            .skip_rows(chunk * chunk_row_cnt)
                                                            .num_rows(rows_to_read)
                                                            .build();

        auto result = cudf::io::read_parquet(read_options); // Using the default stream implicitly
        total_rows_read += result.tbl->num_rows();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Total rows read: " << total_rows_read << std::endl;
    std::cout << "Total read time: " << duration << " ms" << std::endl;

    return 0;
}
