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

# the pantora axf dependency consists of a set of packages

# assuming the find_pantora_axf_ext script was successful
# if not, this is an error case. The corresponding project should not have been selected for build.
if(NOT MDL_PANTORA_AXF_FOUND)
    message(FATAL_ERROR "The dependency \"${__TARGET_ADD_DEPENDENCY_DEPENDS}\" for target \"${__TARGET_ADD_DEPENDENCY_TARGET}\" could not be resolved.")
else()

    # headers
    target_include_directories(${__TARGET_ADD_DEPENDENCY_TARGET} 
        PRIVATE
            ${MDL_DEPENDENCY_PANTORA_AXF_INCLUDE}
        )

    # static library
    target_link_libraries(${__TARGET_ADD_DEPENDENCY_TARGET} 
        PRIVATE
            ${MDL_DEPENDENCY_PANTORA_AXF_LIBS}
        )

    # copy runtime dependencies
    # copy system libraries only on windows, we assume the libraries are installed in a unix environment
    if(WINDOWS)
        if(NOT __TARGET_ADD_DEPENDENCY_NO_RUNTIME_COPY)
            target_copy_to_output_dir(TARGET ${__TARGET_ADD_DEPENDENCY_TARGET}
                FILES
                    ${MDL_DEPENDENCY_PANTORA_AXF_SHARED}
                )
        endif()
    else()
        # add the shared lib path as RPATH
        foreach(_SHARED ${MDL_DEPENDENCY_PANTORA_AXF_SHARED})
        get_filename_component(_SHARED_DIR ${_SHARED} DIRECTORY)
        target_add_rpath(TARGET ${__TARGET_ADD_DEPENDENCY_TARGET}
                RPATHS ${_SHARED_DIR}
            )
        endforeach()
    endif()
endif()
