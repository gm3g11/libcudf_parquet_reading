1. lib_arrow.cpp: g++ -O3 -fopenmp -o arrow_parquet -std=c++17 lib_arrow.cpp  -lparquet -larrow -lgomp
threads_num: 8 
54ms (w/ and w/o threads have the similar latency, 54ms vs 52ms)

2. parquet_read_baseline.cpp: 
using pool_memory (rmm::mr::pool_memory_resource mr{&cuda_mr, rmm::percent_of_free_device_memory(80)};)
w/o pool_memory, we have a similar time (115ms vs 114ms)
In the previous version (24.04 version), parquet_read needs 299ms
default threads number: 8, default streams number: 7

3. parquet_ramfs.cpp: 136ms
Here is my implementation:
    1. sudo mkdir /mnt/ramfs
    2. sudo mount -t tmpfs -o size=100G tmpfs /mnt/ramfs
    3. cp part-00198-tid-3747487300473043810-11eb4400-583b-4bd3-9c6c-a9803c7aeb94-3334-1-c000.snappy.parquet /mnt/ramfs/
In the parquet_ramfs file, I read parquet file from the mnt directory:
auto options=cudf::io::parquet_reader_options::builder(cudf::io::source_info("/mnt/ramfs/part-00198-tid-3747487300473043810-11eb4400-583b-4bd3-9c6c-a9803c7aeb94-3334-1-c000.snappy.parquet"));


4. chuked_parquet_read_API: 121ms with chunk_num =1 (default), 143ms with chunk_num=2, 160ms with chunk_num=3, 388ms with chunk_num=6
We can set up chunk_read_limit and pass_read_limit with different size instead of explicitely setting up the chunk_number or row_number

5. chunked_parquet_read_self_implementation: 127ms with chunk_num=1
This code has a similar time to the original chuked_parquet_read (API), but can directly set up the chunk_num in this code.


6. chunked_parquet_read_self_implementation + no_compression: 44ms with chunk_num=1 and uncompressed parquet file.

7. chunked_parquet_read_self_implementation + uncompressed_data + multi-streams: 37ms with chunk_num=1, streams=4 and uncompressed file.
Even we set up multi-streams, but it still uses 7 streams as the default stream number. We think this is because the row number is too small.

8. chunked_parquet_read_self_implementation + uncompressed_data + multi-streams + multi-threads: 112 ms, 4 chunks, 4 threads, 4 streams
We have 21 streams and 11 threads in this case. 4 chunks without multi-threads need 146ms.


