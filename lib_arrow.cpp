// g++ -O3 -fopenmp -o arrow_parquet -std=c++17 lib_arrow.cpp  -lparquet -larrow -lgomp
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <chrono>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <numa.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>
#include <string>
#include <unistd.h>
#include <vector>

void arrow_runtime_print() {
  arrow::RuntimeInfo rtinfo = arrow::GetRuntimeInfo();
  std::cout << "arrow runtime SIMD level " << rtinfo.simd_level << std::endl;
  int NUM_IOThreads = arrow::io::GetIOThreadPoolCapacity();
  std::cout << "num io threads " << NUM_IOThreads << std::endl;
}

void get_metadata_and_print(std::string filepath, int &num_row_group,
                            std::vector<std::string> &names) {
  std::unique_ptr<parquet::ParquetFileReader> parquet_reader =
      parquet::ParquetFileReader::OpenFile(filepath, false);
  std::shared_ptr<arrow::io::ReadableFile> infile;
  PARQUET_ASSIGN_OR_THROW(
      infile, arrow::io::ReadableFile::Open(filepath.c_str(),
                                            arrow::default_memory_pool()));
  std::unique_ptr<parquet::arrow::FileReader> reader;

  PARQUET_THROW_NOT_OK(
      parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));

  auto file_metadata = parquet_reader->metadata();
  std::shared_ptr<::arrow::Schema> schema;
  // reader->GetSchema(&schema);
  arrow::Status status = reader->GetSchema(&schema);
  if (!status.ok()) {
      // Handle the error, for example, by logging or throwing an exception
      std::cerr << "Error getting schema: " << status.ToString() << std::endl;
      exit(-1);
  }

  auto column_names = schema->field_names();
  names = column_names;
  int num_groups = file_metadata->num_row_groups();
  num_row_group = num_groups;
}

void read_files_by_group_column(std::string filepath, bool use_threads,
                                int num_groups, int num_columns) {
  std::cout << "Reading " << filepath << std::endl;
  std::shared_ptr<arrow::io::ReadableFile> infile;
  arrow::MemoryPool *MP;
  auto st = arrow::jemalloc_memory_pool(&MP);
  if (!st.ok()) {
    std::cerr << "failed to create jemalloc MP\n";
    exit(-1);
  } else {
    MP = arrow::system_memory_pool();
  }

  PARQUET_ASSIGN_OR_THROW(infile,
                          arrow::io::ReadableFile::Open(filepath.c_str(), MP));
  std::unique_ptr<parquet::arrow::FileReader> reader;
  PARQUET_THROW_NOT_OK(parquet::arrow::OpenFile(infile, MP, &reader));

  reader->set_use_threads(use_threads);

  const int loops = 1;
  auto start = std::chrono::steady_clock::now();
  int total_rows = 0;
  std::vector<std::vector<std::shared_ptr<arrow::ChunkedArray>>> ColChunk(
      num_groups);
  for (auto &tbl : ColChunk) {
    tbl.resize(num_columns);
  }
  
  for (int i = 0; i < loops; i++) {
#pragma omp parallel for collapse(2)
    for (int r = 0; r < num_groups; r++) {
      for (int c = 0; c < num_columns; c++) {
        PARQUET_THROW_NOT_OK(
            reader->RowGroup(r)->Column(c)->Read(&ColChunk[r][c]));
            // std::shared_ptr<parquet::RowGroupMetaData> rg_meta = file_metadata->RowGroup(i);
            // total_rows += rg_meta->num_rows();
      }
    }
  }
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end - start;

  std::cout << "read_files_by_group_column time elapsed "
            << (std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                      start))
                       .count() *
                   1.0 / loops
            << " ms\n";
  std::cout << std::endl;
}


int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "needs at least 3 param:\n\t program <filepath> <true|false>"
              << std::endl;
    exit(-1);
  }
  std::string filepath = argv[1];
  std::string use_threads = argv[2];

  bool column_parallel = false;
  if (use_threads == std::string("true")) {
    column_parallel = true;
  }
  int num_groups = 0;
  int num_columns{0};
  std::vector<std::string> names;
  arrow_runtime_print();
  get_metadata_and_print(filepath, num_groups, names);
  num_columns = names.size();
  read_files_by_group_column(filepath, column_parallel, num_groups,
                             num_columns);
  return 0;
}