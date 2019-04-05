cmake_minimum_required(VERSION 3.13)
project(ThresholdingITK)

set(CMAKE_CXX_STANDARD 14)

find_package(ITK)
include(${ITK_USE_FILE})

add_executable(ThresholdingITKBuild Thresholding.cpp)

target_link_libraries(ThresholdingITKBuild ${ITK_LIBRARIES})
