cmake_minimum_required(VERSION 3.27)
project(verification CXX C)

# 获取当前目录下的所有cpp文件
get_all_sources(${CMAKE_CURRENT_SOURCE_DIR} all_cpp_files_list)

if("${all_cpp_files_list}" STREQUAL "")
    message(WARNING "This folder has no headers or sources!!!")
else()
    foreach(_cpp_file_path ${all_cpp_files_list})
        string(REGEX MATCH "[A-Za-z0-9_\+-]*\.cpp" _cpp_file_name ${_cpp_file_path})
        string(REPLACE ".cpp" "" _cpp_file_name_without_format ${_cpp_file_name})
        set(TMP_TARGET_NAME "${PROJECT_NAME}_${_cpp_file_name_without_format}")

        # 添加可执行文件
        add_executable(${TMP_TARGET_NAME} ${_cpp_file_path})
        set_property(TARGET ${TMP_TARGET_NAME} PROPERTY FOLDER "${PROJ_PROPERTY_PREFIX}/application/verification")

        # 设置目标引用
        target_include_directories(${TMP_TARGET_NAME} PUBLIC ${PROJ_COMMON_INCLUDE_DIRS})

        # 设置目标链接
        target_link_libraries(${TMP_TARGET_NAME} PUBLIC ${PROJ_TARGET_NAME})
    endforeach(_cpp_file_path ${all_cpp_files_list})
endif()
