#include <cudf/aggregation.hpp>
#include <cudf/groupby.hpp>
#include <cudf/io/csv.hpp>
#include <cudf/table/table.hpp>

#include <rmm/cuda_device.hpp>
#include <rmm/mr/device/cuda_memory_resource.hpp>
#include <rmm/mr/device/device_memory_resource.hpp>
#include <rmm/mr/device/pool_memory_resource.hpp>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <vector>

#include <map>
#include <rmm/device_buffer.hpp>

#include <cudf/column/column.hpp>
#include <cudf/lists/lists_column_view.hpp>
#include <cudf/lists/count_elements.hpp>
#include <cudf/column/column_view.hpp>
#include <cudf/concatenate.hpp>
#include <cudf/io/parquet.hpp>
#include <cudf/table/table.hpp>
#include <cudf/table/table_view.hpp>
#include <cudf/types.hpp>
// #include <cudf/io/text/detail/multibyte_split.hpp>

// #include <nvbench/nvbench.cuh>
int main(int argc, char** argv)
{
    rmm::mr::cuda_memory_resource cuda_mr{};
    rmm::mr::pool_memory_resource<rmm::mr::cuda_memory_resource> pool_mr(&cuda_mr, 0, rmm::percent_of_free_device_memory(80));
    rmm::mr::set_current_device_resource(&pool_mr);

    auto read_opts = cudf::io::parquet_reader_options::builder(cudf::io::source_info("../dataset/part-00198-tid-3747487300473043810-11eb4400-583b-4bd3-9c6c-a9803c7aeb94-3334-1-c000.snappy.parquet")).build();
    
    // Get the current device memory resource
    auto mr = rmm::mr::get_current_device_resource();
    // Set the chunk and pass read limits (in bytes)
    std::size_t chunk_read_limit = 1024 * 1024 * 40; // For example, 30 MB per chunk
    std::size_t pass_read_limit = 1024 * 1024 * 10; 
    cudf::size_type num_rows_read = 0;
      
    // Construct the reader without explicitly specifying the stream
    auto reader = cudf::io::chunked_parquet_reader(0 ,pass_read_limit,read_opts, cudf::get_default_stream(),mr);
    int chunk_count = 0;
    auto start = std::chrono::steady_clock::now();
    do {        
        auto const result = reader.read_chunk();      
        num_rows_read += result.tbl->num_rows();
        chunk_count++;
    } while (reader.has_next());

    auto end = std::chrono::steady_clock::now();

    std::cout << "Chunked reading parquet file time elapsed "
              << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count()
              << " ms\n";
    std::cout << "Number of chunks read: " << chunk_count << std::endl;
    std::cout << "Total row number: " << num_rows_read << std::endl;
    
    return 0;
}
