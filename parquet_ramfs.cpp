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


int main(int argc, char** argv)
{
  rmm::mr::cuda_memory_resource cuda_mr{};
  rmm::mr::pool_memory_resource mr{&cuda_mr, rmm::percent_of_free_device_memory(80)};
  rmm::mr::set_current_device_resource(&mr);

  auto options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(
    "/mnt/ramfs/part-00198-tid-3747487300473043810-11eb4400-583b-4bd3-9c6c-a9803c7aeb94-3334-1-c000.snappy.parquet")).build();
  // Removed unnecessary comment line for clarity

  auto table_result = cudf::io::read_parquet(options);
  // Assuming table_result holds the result of read_parquet, which should have methods to get metadata, rows, and columns
  std::cout << "Read parquet file with " << table_result.tbl->num_rows() << " rows and " << table_result.tbl->num_columns() << " columns." << std::endl;

  const int loops = 1;
  auto start = std::chrono::steady_clock::now();

  for (int i = 0; i < loops; i++) {
      auto table = cudf::io::read_parquet(options);
  }

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end - start;

  std::cout << "reading parquet file time elapsed "
            << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count()
            << " ms\n";


  return 0;
}

