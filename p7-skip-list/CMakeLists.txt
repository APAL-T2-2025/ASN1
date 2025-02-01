cmake_minimum_required(VERSION 3.30)
project(skip_list)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        nanobench
        GIT_REPOSITORY https://github.com/martinus/nanobench.git
        GIT_TAG v4.1.0
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nanobench)

#option(BENCHMARK_ENABLE_TESTING "Enable Google Benchmark tests" OFF)
#option(BENCHMARK_DOWNLOAD_DEPENDENCIES "Download dependencies" ON)

#FetchContent_Declare(
#        google_benchmark
#        GIT_REPOSITORY https://github.com/google/benchmark.git
#        GIT_TAG        v1.9.1
#)
#set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(google_benchmark)

add_executable(skip_list
        main.cc
        apal/skip_list.cc
        apal/skip_list.h
)

target_include_directories(skip_list
        PRIVATE
        ${nanobench_SOURCE_DIR}
)

target_link_libraries(skip_list
        PRIVATE
#        benchmark::benchmark
#        benchmark::benchmark_main
        nanobench
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS -O3)
endif()
