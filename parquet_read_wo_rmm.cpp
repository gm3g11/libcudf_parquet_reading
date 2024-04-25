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
#include <cuda_runtime.h>
#include <cudf/column/column.hpp>
#include <cudf/lists/lists_column_view.hpp>
#include <cudf/lists/count_elements.hpp>
#include <cudf/column/column_view.hpp>
#include <cudf/concatenate.hpp>
#include <cudf/io/parquet.hpp>
#include <cudf/table/table.hpp>
#include <cudf/table/table_view.hpp>
#include <cudf/types.hpp>
#include <chrono>

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <parquet_file_path>" << std::endl;
    return 1;
  }

  std::string file_path = argv[1];
  cudaEvent_t startEvent, stopEvent;
  cudaEventCreate(&startEvent);
  cudaEventCreate(&stopEvent);

  auto options = cudf::io::parquet_reader_options::builder(cudf::io::source_info(file_path)).build();

  cudaEventRecord(startEvent);
  auto table = cudf::io::read_parquet(options);
  cudaEventRecord(stopEvent);
  cudaEventSynchronize(stopEvent);

  float milliseconds = 0;
  cudaEventElapsedTime(&milliseconds, startEvent, stopEvent);

  std::cout << "Reading parquet file kernel time elapsed: " << milliseconds << " ms" << std::endl;

  return 0;
}
