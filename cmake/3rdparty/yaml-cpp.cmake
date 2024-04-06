function(find_yamlcpp)
    message(STATUS "=================================================================")
    message(STATUS "Start finding third party: yaml-cpp.")

    # find in system
    find_package(yaml-cpp CONFIG QUIET)

    if(NOT ${yaml-cpp_FOUND})
        message(WARNING "Yaml-cpp NOT found in system.")

        set(YAML_CPP_FORMAT_SOURCE OFF)
        set(YAML_CPP_INSTALL ON)

        # Fetch
        include(FetchContent)
        message(STATUS "Start FetchContent_Declare: yaml-cpp.")
        FetchContent_Declare(
            yamlcpp
            PREFIX "${CMAKE_BINARY_DIR}/_deps/yaml-cpp"
            GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
            GIT_TAG 0.8.0)

        message(STATUS "Start FetchContent_MakeAvailable: yaml-cpp.")
        FetchContent_MakeAvailable(yamlcpp)
        message(STATUS "Fetch Over: yaml-cpp.")
    else()
        message(STATUS "Third party found: fmt.")
    endif()

    message(STATUS "=================================================================")
endfunction(find_yamlcpp)
