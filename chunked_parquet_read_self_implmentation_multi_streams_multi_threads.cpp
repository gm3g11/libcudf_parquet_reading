#include <cudf/io/parquet.hpp>
#include <rmm/mr/device/cuda_memory_resource.hpp>
#include <rmm/mr/device/per_device_resource.hpp>
#include <rmm/cuda_stream.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <file_path> <num_chunks> <num_threads>" << std::endl;
        return 1;
    }

    const std::string file_path = argv[1];
    const int num_chunks = std::stoi(argv[2]);
    const int num_threads = std::stoi(argv[3]);
    
    // Initialize CUDA memory resource
    rmm::mr::cuda_memory_resource cuda_mr;
    rmm::mr::set_current_device_resource(&cuda_mr);

    // Read the entire file to determine total number of rows
    auto total_row_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path)).build();
    auto total_row_table = cudf::io::read_parquet(total_row_options);
    const int total_rows = total_row_table.tbl->num_rows();
    const int rows_per_chunk = total_rows / num_chunks;

    std::vector<rmm::cuda_stream> streams(num_threads);
    std::vector<std::thread> workers;
    std::mutex io_mutex;
    int total_rows_read = 0;

    auto read_chunk = [&](int chunk_index) {
        int start_row = chunk_index * rows_per_chunk;
        int end_row = (chunk_index == num_chunks - 1) ? total_rows : (start_row + rows_per_chunk);

        cudf::io::parquet_reader_options read_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path))
                                                            .skip_rows(start_row)
                                                            .num_rows(end_row - start_row)
                                                            .build();

        // Read part of the file using a dedicated stream
        auto table = cudf::io::read_parquet(read_options, streams[chunk_index % num_threads]);
        
        // Use mutex to safely update the shared variable
        std::lock_guard<std::mutex> lock(io_mutex);
        total_rows_read += table.tbl->num_rows();
    };

    // Create and initialize streams
    for (int i = 0; i < num_threads; ++i) {
        streams[i] = rmm::cuda_stream();
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    // Start threads
    for (int i = 0; i < num_chunks; ++i) {
        workers.emplace_back(std::thread(read_chunk, i));
    }

    // Join threads
    for (auto& worker : workers) {
        worker.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Total rows read: " << total_rows_read << std::endl;
    std::cout << "Total read time: " << duration << " ms" << std::endl;

    return 0;
}
