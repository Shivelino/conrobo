# 构建选项
set(BUILD_EXPERIMENT
    "ON"
    CACHE BOOL "Whether to build the module: experiment")
set(BUILD_VERIFICATION
    "ON"
    CACHE BOOL "Whether to build the module: verification")

# 增加子项目
if(${BUILD_EXPERIMENT})
    add_subdirectory(experiment)
endif()

if(${BUILD_VERIFICATION})
    add_subdirectory(verification)
endif()
