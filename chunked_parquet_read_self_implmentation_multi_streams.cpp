#include <cudf/io/parquet.hpp>
#include <rmm/cuda_stream_view.hpp>
#include <rmm/mr/device/cuda_memory_resource.hpp>
#include <rmm/mr/device/per_device_resource.hpp>
#include <chrono>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <file_path> <num_streams> <num_chunks>" << std::endl;
        return 1;
    }

    const std::string file_path = argv[1];
    const int32_t num_streams = std::stoi(argv[2]);
    const int32_t chunked_read_num_chunks = std::stoi(argv[3]);

    // Initialize CUDA memory resource
    rmm::mr::cuda_memory_resource cuda_mr;
    rmm::mr::set_current_device_resource(&cuda_mr);

    std::vector<rmm::cuda_stream> streams(num_streams);
    for (int32_t i = 0; i < num_streams; ++i) {
        streams[i] = rmm::cuda_stream();
    }

    // Read the entire file to determine total number of rows
    auto total_row_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path)).build();
    auto total_row_table = cudf::io::read_parquet(total_row_options, streams[0]);  // Use the first stream to read metadata
    const int32_t total_rows = total_row_table.tbl->num_rows();

    int32_t chunk_row_cnt = total_rows / chunked_read_num_chunks;
    cudf::size_type total_rows_read = 0;

    int32_t streams_per_chunk = num_streams / chunked_read_num_chunks;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int32_t chunk = 0; chunk < chunked_read_num_chunks; ++chunk) {
        for (int32_t sub_chunk = 0; sub_chunk < streams_per_chunk; ++sub_chunk) {
            int32_t stream_index = chunk * streams_per_chunk + sub_chunk;
            int32_t sub_chunk_row_start = chunk * chunk_row_cnt + (sub_chunk * (chunk_row_cnt / streams_per_chunk));
            int32_t sub_chunk_row_count = (sub_chunk == streams_per_chunk - 1) ? 
                (chunk_row_cnt - sub_chunk * (chunk_row_cnt / streams_per_chunk)) : 
                (chunk_row_cnt / streams_per_chunk);

            cudf::io::parquet_reader_options read_options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path))
                                                                .skip_rows(sub_chunk_row_start)
                                                                .num_rows(sub_chunk_row_count)
                                                                .build();
            auto result = cudf::io::read_parquet(read_options, streams[stream_index]);
            total_rows_read += result.tbl->num_rows();
        }
    }

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
