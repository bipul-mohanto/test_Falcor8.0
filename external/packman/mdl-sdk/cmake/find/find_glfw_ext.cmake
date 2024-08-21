#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

function(FIND_GLFW_EXT)

    set(GLFW_DIR "" CACHE PATH "Directory that contains the glfw include dir, libs and binaries")

    if(NOT MDL_ENABLE_OPENGL_EXAMPLES AND NOT MDL_ENABLE_VULKAN_EXAMPLES)
        message(WARNING "Examples that require GLFW are disabled. Enable the option 'MDL_ENABLE_OPENGL_EXAMPLES' or/and 'MDL_ENABLE_VULKAN_EXAMPLES' and resolve the required dependencies to re-enable them.")
        return()
    endif()

    find_package(glfw3 QUIET)
    if(glfw3_FOUND)
        set(_GLFW_INCLUDE ${GLFW_INCLUDE_DIR})
        set(_GLFW_SHARED glfw)
    else()
        # try to find GLFW manually
        set(_GLFW_INCLUDE "NOTFOUND")
        set(_GLFW_LIB "NOTFOUND")
        set(_GLFW_SHARED "NOTFOUND")
        mark_as_advanced(glfw3_DIR)

        if(EXISTS ${GLFW_DIR})
            set(_GLFW_INCLUDE ${GLFW_DIR}/include)

            # assuming that the windows (x64) binaries from http://www.glfw.org/download.html are used
            if(WINDOWS)
                set(_GLFW_LIB "${GLFW_DIR}/lib-vc2015/glfw3dll.lib")
                set(_GLFW_SHARED "${GLFW_DIR}/lib-vc2015/glfw3.dll")

            else()
                # link dynamic
                set(_GLFW_LIB "")  # not used
                find_file(_GLFW_SHARED "${CMAKE_SHARED_LIBRARY_PREFIX}glfw${CMAKE_SHARED_LIBRARY_SUFFIX}"
                    HINTS 
                        ${GLFW_DIR}
                        ${GLFW_DIR}/lib64
                        ${GLFW_DIR}/lib
                        /usr/lib64/
                        /usr/lib/x86_64-linux-gnu
                        /usr/lib
                    )
            endif()
        endif()

        # error if dependencies can not be resolved
        if(NOT EXISTS ${_GLFW_INCLUDE} OR (WINDOWS AND NOT EXISTS ${_GLFW_LIB}) OR NOT EXISTS ${_GLFW_SHARED})
            message(STATUS "GLFW_DIR: ${GLFW_DIR}")
            message(STATUS "_GLFW_INCLUDE: ${_GLFW_INCLUDE}")
            message(STATUS "_GLFW_LIB: ${_GLFW_LIB}")
            message(STATUS "_GLFW_SHARED: ${_GLFW_SHARED}")
            message(FATAL_ERROR "The dependency \"glfw\" could not be resolved. Please specify GLFW_DIR. Alternatively, you can disable the option 'MDL_ENABLE_OPENGL_EXAMPLES'.")
        endif()
    endif()

    # store path that are later used in the add_opengl.cmake
    set(MDL_DEPENDENCY_GLFW_INCLUDE ${_GLFW_INCLUDE} CACHE INTERNAL "glfw headers")
    set(MDL_DEPENDENCY_GLFW_LIBS ${_GLFW_LIB} CACHE INTERNAL "glfw libs")
    set(MDL_DEPENDENCY_GLFW_SHARED ${_GLFW_SHARED} CACHE INTERNAL "glfw shared libs")
    set(MDL_GLFW_FOUND ON CACHE INTERNAL "")

    if(MDL_LOG_DEPENDENCIES)
        message(STATUS "[INFO] MDL_DEPENDENCY_GLFW_INCLUDE:          ${MDL_DEPENDENCY_GLFW_INCLUDE}")
        message(STATUS "[INFO] MDL_DEPENDENCY_GLFW_LIBS:             ${MDL_DEPENDENCY_GLFW_LIBS}")
        message(STATUS "[INFO] MDL_DEPENDENCY_GLFW_SHARED:           ${MDL_DEPENDENCY_GLFW_SHARED}")
    endif()

endfunction()
