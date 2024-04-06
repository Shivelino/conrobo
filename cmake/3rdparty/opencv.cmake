function(find_opencv)
    message(STATUS "=================================================================")
    message(STATUS "Start finding third party: opencv.")

    # find in system
    find_package(OpenCV QUIET)

    if(NOT ${OpenCV_FOUND})
        message(FATAL_ERROR "Third party NOT found in system.")
    endif()

    set(Conrobo_OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS} PARENT_SCOPE)
    set(Conrobo_OpenCV_LIBRARIES ${OpenCV_LIBS} PARENT_SCOPE)
    set(_Conrobo_OpenCV_BIN_DIR)

    if(WIN32)
        set(_Conrobo_OpenCV_BIN_DIR "${OpenCV_INSTALL_PATH}/x64/vc16/bin")
    endif()

    set(Conrobo_OpenCV_BIN_DIR ${_Conrobo_OpenCV_BIN_DIR} PARENT_SCOPE)

    message(STATUS "=================================================================")
endfunction(find_opencv)

function(target_include_opencv _target_name)
    target_include_directories(${_target_name} PUBLIC ${Conrobo_OpenCV_INCLUDE_DIRS})
endfunction(target_include_opencv _target_name)

function(target_link_opencv _target_name _dll_dest_dir)
    target_link_libraries(${_target_name} PUBLIC ${Conrobo_OpenCV_LIBRARIES})

    file(GLOB_RECURSE _moving_dlls "${Conrobo_OpenCV_BIN_DIR}/*.dll")

    foreach(dll_file ${_moving_dlls})
        add_custom_command(
            TARGET ${_target_name}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${dll_file} ${_dll_dest_dir})
    endforeach(dll_file ${_moving_dlls})
endfunction(target_link_opencv _target_name _dll_dest_dir)
