include("/home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/cmake/CPM_0.35.3.cmake")
CPMAddPackage("NAME;GTest;VERSION;1.13.0;FIND_PACKAGE_ARGUMENTS;EXACT;GIT_REPOSITORY;https://github.com/google/googletest.git;GIT_TAG;v1.13.0;GIT_SHALLOW;ON;EXCLUDE_FROM_ALL;OFF;OPTIONS;INSTALL_GTEST ON;CMAKE_POSITION_INDEPENDENT_CODE ON")
set(GTest_FOUND TRUE)