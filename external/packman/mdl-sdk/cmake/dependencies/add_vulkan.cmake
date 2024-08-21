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

# the vulkan dependency consists of a set of packages

# assuming the find_vulkan_ext script was successful
# if not, this is an error case. The corresponding project should not have been selected for build.
if(NOT MDL_ENABLE_VULKAN_EXAMPLES)
    message(FATAL_ERROR "The dependency \"${__TARGET_ADD_DEPENDENCY_DEPENDS}\" for target \"${__TARGET_ADD_DEPENDENCY_TARGET}\" could not be resolved.")
else()

    # headers
    target_include_directories(${__TARGET_ADD_DEPENDENCY_TARGET} 
        PRIVATE
            ${MDL_DEPENDENCY_VULKAN_INCLUDE}
            ${MDL_DEPENDENCY_GLSLANG_INCLUDE}
        )

    # static library
    if(WIN32)
        target_link_libraries(${__TARGET_ADD_DEPENDENCY_TARGET} 
            PRIVATE
                ${MDL_DEPENDENCY_VULKAN_LIBS}
            )
        foreach (_LIB ${MDL_DEPENDENCY_GLSLANG_LIBS})
            target_link_libraries(${__TARGET_ADD_DEPENDENCY_TARGET} PRIVATE optimized ${_LIB})
        endforeach()
        foreach (_LIB ${MDL_DEPENDENCY_GLSLANG_LIBS_DEBUG})
            target_link_libraries(${__TARGET_ADD_DEPENDENCY_TARGET} PRIVATE debug ${_LIB})
        endforeach()

        # The glslang libs don't include pdb files causing linker warnings
        set_target_properties(${__TARGET_ADD_DEPENDENCY_TARGET} PROPERTIES LINK_FLAGS "/ignore:4099")
    else()
        target_link_libraries(${__TARGET_ADD_DEPENDENCY_TARGET} 
            PRIVATE
                ${MDL_DEPENDENCY_VULKAN_LIBS}
                ${MDL_DEPENDENCY_GLSLANG_LIBS}
            )
    endif()

    # runtime dependencies
    if(MDL_DEPENDENCY_VULKAN_BIN)
        if(WIN32)
            target_add_vs_debugger_env_var(TARGET ${__TARGET_ADD_DEPENDENCY_TARGET}
                VARS
                    "VK_LAYER_PATH=${MDL_DEPENDENCY_VULKAN_BIN}"
                )
        endif()

        # on linux and mac, the user has to setup the VK_LAYER_PATH when running examples.
        # on mac, the user also has to setup the VK_ICD_FILENAMES when running examples.
    endif()

endif()
