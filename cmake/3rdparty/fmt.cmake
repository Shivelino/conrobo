function(find_fmt)
    message(STATUS "=================================================================")
    message(STATUS "Start finding third party: fmt.")

    # find in system
    find_package(fmt CONFIG QUIET)

    if(NOT ${fmt_FOUND})
        message(WARNING "FMT NOT found in system.")

        # Options
        set(FMT_INSTALL OFF)

        # Fetch
        include(FetchContent)
        message(STATUS "Start FetchContent_Declare: fmt.")
        FetchContent_Declare(
            fmt
            PREFIX "${CMAKE_BINARY_DIR}/_deps/fmt"
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 10.1.1) # OVERRIDE_FIND_PACKAGE
        message(STATUS "Start FetchContent_MakeAvailable: fmt.")
        FetchContent_MakeAvailable(fmt)
        message(STATUS "Fetch Over: fmt.")
    else()
        message(STATUS "Third party found: fmt.")
    endif()

    message(STATUS "=================================================================")
endfunction(find_fmt)
