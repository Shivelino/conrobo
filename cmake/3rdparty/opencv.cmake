function(find_opencv)
    message(STATUS "=================================================================")
    message(STATUS "Start finding third party: opencv.")

    # find in system
    find_package(opencv CONFIG REQUIRED)

    message(STATUS "=================================================================")
endfunction(find_opencv)

macro(target_include_opencv _target_name)
    target_include_directories(${_target_name} PUBLIC ${OpenCV_INCLUDE_DIRS})
endmacro(target_include_opencv _target_name)

macro(target_link_opencv _target_name)
    target_link_libraries(${_target_name} PUBLIC ${OpenCV_LIBRARIES})
endmacro(target_link_opencv _target_name)
