#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

# -------------------------------------------------------------------------------------------------
# script expects the following variables:
# - __TARGET_ADD_DEPENDENCY_TARGET
# - __TARGET_ADD_DEPENDENCY_DEPENDS
# - __TARGET_ADD_DEPENDENCY_COMPONENTS
# - __TARGET_ADD_DEPENDENCY_NO_RUNTIME_COPY
# - __TARGET_ADD_DEPENDENCY_NO_LINKING
# -------------------------------------------------------------------------------------------------

# add include directories and link dependencies
target_include_directories(${__TARGET_ADD_DEPENDENCY_TARGET} 
    PRIVATE
        ${MDL_INCLUDE_FOLDER}
    )

# instead of copying, we add the library paths the debugger environment
if(NOT __TARGET_ADD_DEPENDENCY_NO_RUNTIME_COPY)
    if(WINDOWS)
        target_add_vs_debugger_env_path(TARGET ${__TARGET_ADD_DEPENDENCY_TARGET}
            PATHS 
                ${MDL_BASE_FOLDER}/nt-x86-64/lib
            )
    else()
        # for unix systems we can set the rpath to guide the library resolution
        target_add_rpath(TARGET ${__TARGET_ADD_DEPENDENCY_TARGET}
            RPATHS ${MDL_BASE_FOLDER}/${MI_PLATFORM_NAME}/lib
            )
    endif()

    # on linux, the user has to setup the LD_LIBRARY_PATH when running examples
    # on mac, DYLD_LIBRARY_PATH, respectively.
endif()
