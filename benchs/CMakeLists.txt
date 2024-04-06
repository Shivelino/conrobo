cmake_minimum_required(VERSION 3.27)
project(benchs CXX C)

# 3rdparty
include("${PROJ_CMAKE_DIR}/3rdparty/benchmark.cmake") # benchmark
find_benchmark()
include("${PROJ_CMAKE_DIR}/3rdparty/fmt.cmake") # fmt
find_fmt()

# benchmark工具文件
set(BENCHS_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp")
source_group("benchmark_utils" FILES ${BENCHS_HEADER_FILES})
set(BENCHS_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
source_group("benchmark_utils" FILES ${BENCHS_SOURCE_FILES})

# benchmark的测试子文件夹
get_all_sources("${CMAKE_CURRENT_SOURCE_DIR}" TMP_SOURCES)
set(BENCHS_SOURCE_FILES ${BENCHS_SOURCE_FILES} ${TMP_SOURCES})

# benchmark可执行文件
set(TMP_TARGET_NAME ${PROJECT_NAME})
add_executable(${TMP_TARGET_NAME} ${BENCHS_HEADER_FILES} ${BENCHS_SOURCE_FILES})
set_property(TARGET ${TMP_TARGET_NAME} PROPERTY FOLDER "${PROJ_PROPERTY_PREFIX}")

# 设置目标引用
target_include_directories(${TMP_TARGET_NAME} PUBLIC ${PROJ_COMMON_INCLUDE_DIRS})

# 设置目标链接
target_link_libraries(${TMP_TARGET_NAME} PUBLIC ${PROJ_TARGET_NAME})
target_link_libraries(${TMP_TARGET_NAME} PUBLIC benchmark::benchmark benchmark::benchmark_main)
target_link_libraries(
    ${TMP_TARGET_NAME}
    PUBLIC debug fmt::fmt-header-only
    PUBLIC optimized fmt::fmt-header-only)

# 指定benchmark的输出形式
add_definitions(-DBENCHMARK_OUTPUT="console") # console, csv/CSV, json/JSON
