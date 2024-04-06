cmake_minimum_required(VERSION 3.27)

include(config.cmake)

# ---------------------------------------------------------------------------------------
# Config Preprocess
# ---------------------------------------------------------------------------------------
string(TOLOWER ${MY_PROJ_NAME} PROJ_NAME_LOWER)
string(TOUPPER ${MY_PROJ_NAME} PROJ_NAME_UPPER)
set(PROJ_VERSION "${MY_PROJ_VERSION_MAJOR}.${MY_PROJ_VERSION_MINOR}.${MY_PROJ_VERSION_PATCH}")

# ---------------------------------------------------------------------------------------
# Start project
# ---------------------------------------------------------------------------------------
project(
    ${PROJ_NAME_LOWER}
    VERSION ${PROJ_VERSION}
    DESCRIPTION ""
    HOMEPAGE_URL ""
    LANGUAGES CXX C)
message(STATUS "Build ${PROJECT_NAME}: ${PROJ_VERSION}")
set(PROJ_PROPERTY_PREFIX ${PROJECT_NAME})

# ---------------------------------------------------------------------------------------
# Set build and c++ options
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        "Release"
        CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(NOT CMAKE_CONFIGURATION_TYPES)
    # Debug;Release;RelWithDebInfo;MinSizeRel
    set(CMAKE_CONFIGURATION_TYPES
        "Debug;Release"
        CACHE STRING "Release and Debug" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # force C++20
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DEBUG_POSTFIX d)

# make sure __cplusplus is defined when using msvc and enable parallel build
if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus /MP")
endif()

# 编译器选项
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # todo
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wno-error)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # todo
endif()

# # 预定义宏
add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DPROJ_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPROJ_LOG_DIR="${CMAKE_CURRENT_SOURCE_DIR}/log")
add_definitions(-DPROJ_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
add_definitions(-DPROJ_CONFIG_DIR="${CMAKE_CURRENT_SOURCE_DIR}/config")

# # 框架路径
set(PROJ_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(PROJ_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(PROJ_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJ_APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/application)
set(PROJ_DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
set(PROJ_SAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/samples)
set(PROJ_DOCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs)
set(PROJ_FORMAT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/format)
set(PROJ_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out)
set(PROJ_BUILD_DEPS_DIR ${PROJ_BUILD_DIR}/_deps) # FetchContent_Declare的工作路径
set(PROJ_COMMON_INCLUDE_DIRS ${PROJ_INCLUDE_DIR} ${PROJ_DEPS_DIR})

# 构建输出directory
set(PROJ_OUT_DIR_DIFF_BUILD_TYPE
    "$<$<CONFIG:Debug>:"
    "${PROJ_OUT_DIR}/Debug"
    ">"
    "$<$<CONFIG:Release>:"
    "${PROJ_OUT_DIR}/Release"
    ">"
    "$<$<CONFIG:RelWithDebInfo>:"
    "${PROJ_OUT_DIR}/RelWithDebInfo"
    ">"
    "$<$<CONFIG:MinSizeRel>:"
    "${PROJ_OUT_DIR}/MinSizeRel"
    ">")
string(REPLACE ";" "" PROJ_OUT_DIR_DIFF_BUILD_TYPE ${PROJ_OUT_DIR_DIFF_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJ_OUT_DIR_DIFF_BUILD_TYPE}) # 可执行Target文件的输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJ_OUT_DIR_DIFF_BUILD_TYPE}) # 共享库Target文件的输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJ_OUT_DIR_DIFF_BUILD_TYPE}) # 静态库Target文件的输出路径
set(PROJ_DLL_OUTPUT_DIR ${PROJ_OUT_DIR_DIFF_BUILD_TYPE}) # DLL文件移动目标路径

# # 框架项目选项
option(PROJ_BUILD_APP "Whether to build the module: application" ON)
option(PROJ_BUILD_TESTS "Whether to build the module: test" ON)
option(PROJ_BUILD_BENCHS "Whether to build the module: benchmark" ON)
option(PROJ_BUILD_FORMAT "Whether to build the format tool" ON)
option(PROJ_BUILD_INSTALL "Generate the install target" ON)
option(PROJ_BUILD_SAMPLES "Whether to build the module: sample" ON) # sample option
option(PROJ_BUILD_DOXYGEN "Whether to build the module: DocGenerate" ON) # doxygen编译开关

# ---------------------------------------------------------------------------------------
# Subdirectory
# ---------------------------------------------------------------------------------------
set(PROJ_TARGET_NAME ${PROJECT_NAME})

include("cmake/utils.cmake")
configure_file("${PROJ_CMAKE_DIR}/version.h.in" "${PROJ_INCLUDE_DIR}/version.h" @ONLY)
get_all_headers(${PROJ_INCLUDE_DIR} TARGET_INCLUDE_FILES) # 获取对应模块所有源文件
get_all_sources(${PROJ_SOURCE_DIR} TARGET_SOURCE_FILES) # 获取对应模块所有源文件

if("${TARGET_SOURCE_FILES}" STREQUAL "")
    message(WARNING "This folder has no sources!!!")
else()
    add_library(${PROJ_TARGET_NAME} STATIC ${TARGET_INCLUDE_FILES} ${TARGET_SOURCE_FILES}) # 添加链接库输出

    set_property(TARGET ${PROJ_TARGET_NAME} PROPERTY FOLDER ${PROJ_PROPERTY_PREFIX})

    # 设置目标引用
    target_include_directories(${PROJ_TARGET_NAME} PUBLIC "$<BUILD_INTERFACE:${PROJ_COMMON_INCLUDE_DIRS}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
endif()

# ---------------------------------------------------------------------------------------
# Binary
# ---------------------------------------------------------------------------------------
if(${PROJ_BUILD_APP})
    add_subdirectory(application)
endif()

if(${PROJ_BUILD_SAMPLES})
    add_subdirectory(samples)
endif()

if(${PROJ_BUILD_TESTS})
    add_subdirectory(tests)
endif()

if(${PROJ_BUILD_BENCHS})
    add_subdirectory(benchs)
endif()

# ---------------------------------------------------------------------------------------
# Chore
# ---------------------------------------------------------------------------------------
if(${PROJ_BUILD_DOXYGEN})
    add_subdirectory(docs)
endif()

# cmake-format
if(${PROJ_BUILD_FORMAT})
    find_package(Python REQUIRED)

    add_custom_target(
        format
        COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/format.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set_property(TARGET format PROPERTY FOLDER "${PROJ_PROPERTY_PREFIX}")

    add_custom_target(
        format-check
        COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/format_check.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set_property(TARGET format-check PROPERTY FOLDER "${PROJ_PROPERTY_PREFIX}")
endif()

# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------
if(PROJ_BUILD_INSTALL)
    message(STATUS "Generating install: ${PROJECT_NAME}")

    set(project_config_in "${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in")
    set(project_config_out "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
    set(config_targets_file "${PROJECT_NAME}ConfigTargets.cmake")
    set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
    set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
    set(pkgconfig_install_dir "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
    set(pkg_config "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc")

    # header and lib files
    install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
    install(
        TARGETS ${PROJ_TARGET_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    # pkg-config file. Bugs Now.
    get_target_property(PKG_CONFIG_DEFINES ${PROJ_TARGET_NAME} INTERFACE_COMPILE_DEFINITIONS) # WARNING no set
    string(REPLACE ";" " -D" PKG_CONFIG_DEFINES "${PKG_CONFIG_DEFINES}")
    string(CONCAT PKG_CONFIG_DEFINES "-D" "${PKG_CONFIG_DEFINES}")
    configure_file("cmake/pc.in" "${pkg_config}" @ONLY)
    install(FILES "${pkg_config}" DESTINATION "${pkgconfig_install_dir}")

    # CMake config files
    export(
        TARGETS ${PROJ_TARGET_NAME}
        NAMESPACE "${PROJECT_NAME}::"
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${config_targets_file}")
    install(
        EXPORT ${PROJ_TARGET_NAME}
        DESTINATION ${export_dest_dir}
        NAMESPACE "${PROJECT_NAME}::"
        FILE ${config_targets_file})

    include(CMakePackageConfigHelpers)
    configure_package_config_file("${project_config_in}" "${project_config_out}" INSTALL_DESTINATION ${export_dest_dir})

    write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
    install(FILES "${project_config_out}" "${version_config_file}" DESTINATION "${export_dest_dir}")

    # Support creation of installable packages
    include("cmake/cpack.cmake")
endif()
