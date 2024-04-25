Compilation steps:

* STEP 1: Create a conda env and Download the RAPIDS
  * conda create -n rapids-24.02 -c rapidsai -c conda-forge -c nvidia rapids=24.02 python=3.10 cuda-version=12.0

* STEP 2: Activate conda env, log into GPU server, and load module

  * conda activate rapids-24.02
  * qrsh -q gpu@@csecri-v100 -l gpu=1 -pe smp 4
  * module load cuda/12.1 cudnn/8.9.3 cmake gcc

* STEP 3: Download the cudf from github:

  * git clone https://github.com/rapidsai/cudf
  * Note that: we need to download 24.02 version although the latest 24.04 comes out.

* STEP 4: Set up libcudf library:

  * cd <path to cudf\>/cpp
  * Put this into the CMakeLists.txt: set(CMAKE_CXX_STANDARD 17)
  * cmake -S . -B ./build -DCMAKE_CUDA_ARCHITECTURES=70 -DCMAKE_CXX_STANDARD=17
  * cmake --build ./build -j4

* STEP 5: Compile your cudf file or example:

  * cd <path to cudf\>/cpp/examples/basic/

  * Configure the CMakeLists.txt with your .cpp file

  * Execute the following build.sh:

    * cmake -S . -B build/ -DCMAKE_CUDA_ARCHITECTURES=70 -DCMAKE_CXX_STANDARD=17 -Dcudf_ROOT=/afs/crc/group/ball_lab/cudf/cpp/build  # setup the libcudf link

    * cmake --build build/ --parallel 4   # compile the project with 4 threads 

    * ./build/basic_example # excute the compiled file

      

Tips:

* Most of the compilation errors are related to the incompatibility of C++ and missing libraries.
* Keep the C++17 standard.
* Double confirm the following libraries are included in the $LD_LIBRARY_PATH:
  * gcc, cuda, conda env. If there are multiple versions of gcc, keep only one
  * Here is an example of $LD_LIBRARY_PATH:
    ![image-20240302231113220](C:\Users\EricG\AppData\Roaming\Typora\typora-user-images\image-20240302231113220.png)





Trouble shooting:

* Cuco issue:

  * ![image-20240302222039458](C:\Users\EricG\AppData\Roaming\Typora\typora-user-images\image-20240302222039458.png)
  * Solution: Check your conda environment with three libraries: **cuda-libraries**`, `**cuda-nvrtc**`, and `**libcufile**

* 'GLIBCXX_3.4.29' not found:

  * /afs/crc/group/ball_lab/cudf/cpp/build/jitify_preprocess: /lib64/libstdc++.so.6: version `GLIBCXX_3.4.29' not found (required by /afs/crc/group/ball_lab/cudf/cpp/build/jitify_preprocess)

    make[2]: *** [CMakeFiles/jitify_preprocess_run.dir/build.make:84: include/jit_preprocessed_files/rolling/jit/kernel.cu.jit.hpp] Error 1

    make[1]: *** [CMakeFiles/Makefile2:929: CMakeFiles/jitify_preprocess_run.dir/all] Error 2

    make[1]: *** Waiting for unfinished jobs....

  * Solution: patchelf --set-rpath /afs/crc.nd.edu/user/g/gmeng/.conda/envs/cl/lib:/afs/crc.nd.edu/x86_64_linux/c/cuda/12.1/targets/x86_64-linux/lib /afs/crc/group/ball_lab/cudf/cpp/build/jitify_preprocessvim (change to your path) 

* rmm issue:

  * [ 50%] Building CXX object CMakeFiles/build.dir/src/process_parquet_update.cpp.o

    /afs/crc/group/ball_lab/cudf/cpp/examples/basic/src/process_parquet_update.cpp:35:10: fatal error: rmm/mr/device_buffer.hpp: No such file or directory

      35 | #include <rmm/mr/device_buffer.hpp>

       |     ^~~~~~~~~~~~~~~~~~~~~~~~~~

    compilation terminated.

  * Solution: 

    * Firstly, double confirm whether rmm is installed in your conda: 
      * conda list rmm
      * If not install, then install it.
    * Secondly, check whether the path of rmm is set in your $LD_LIBRARY_PATH
    * Thirdly, check the .hpp is truely in that directory. Specifically, in this case, the device_buffer.hpp has already been moved into \<rmm> instead of \<rmm/mr>



