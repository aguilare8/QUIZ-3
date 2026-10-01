cmake_minimum_required(VERSION 3.20)

project(Quiz3)

set(CMAKE_CXX_STANDARD 17)

add_executable(benchmarkBS
        binarySearch/benchmarkBS.cpp
)

add_executable(benchmarkMS
        mergeSort/benchmarkMS.cpp
)