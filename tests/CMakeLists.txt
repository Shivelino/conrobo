cmake_minimum_required(VERSION 3.27)
project(tests CXX C)

# 3rdparty
include("${PROJ_CMAKE_DIR}/3rdparty/googletest.cmake") # googletest
find_gtest()
include("${PROJ_CMAKE_DIR}/3rdparty/fmt.cmake") # fmt
find_fmt()

# tests工具文件
set(TEST_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp")
source_group("tests_util" FILES ${TEST_HEADER_FILES})
set(TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
source_group("tests_util" FILES ${TEST_SOURCE_FILES})

# tests的测试子文件夹
get_all_sources("${CMAKE_CURRENT_SOURCE_DIR}" TMP_SOURCES)
set(TEST_SOURCE_FILES ${TEST_SOURCE_FILES} ${TMP_SOURCES})

# benchmark可执行文件
set(TMP_TARGET_NAME ${PROJECT_NAME})
add_executable(${TMP_TARGET_NAME} ${TEST_HEADER_FILES} ${TEST_SOURCE_FILES})
set_property(TARGET ${TMP_TARGET_NAME} PROPERTY FOLDER "${PROJ_PROPERTY_PREFIX}")

# 设置目标引用
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJ_COMMON_INCLUDE_DIRS})

# 设置目标链接
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJ_TARGET_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC gtest gtest_main)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC debug fmt::fmt-header-only
    PUBLIC optimized fmt::fmt-header-only)
