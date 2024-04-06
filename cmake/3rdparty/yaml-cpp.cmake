function(find_yamlcpp)
    message(STATUS "=================================================================")
    message(STATUS "Start finding third party: yaml-cpp.")

    if(NOT POLICY CMP0077)
        message(STATUS "Set CMP0077 OLD.")
        cmake_policy(SET CMP0077 OLD)
    endif()

    # find in system
    find_package(yaml-cpp CONFIG QUIET)

    if(NOT ${yaml-cpp_FOUND})
        message(WARNING "Yaml-cpp NOT found in system.")

        set(YAML_CPP_FORMAT_SOURCE OFF)
        set(YAML_CPP_INSTALL OFF)

        # Fetch
        include(FetchContent)
        message(STATUS "Start FetchContent_Declare: yaml-cpp.")
        FetchContent_Declare(
            yamlcpp
            PREFIX "${CMAKE_BINARY_DIR}/_deps/yaml-cpp"
            GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
            GIT_TAG 0.8.0
            CMAKE_ARGS -DYAML_CPP_FORMAT_SOURCE=OFF)

        message(STATUS "Start FetchContent_MakeAvailable: yaml-cpp.")
        FetchContent_MakeAvailable(yamlcpp)
        message(STATUS "Fetch Over: yaml-cpp.")
    else()
        message(STATUS "Third party found: fmt.")
    endif()

    message(STATUS "=================================================================")
endfunction(find_yamlcpp)
