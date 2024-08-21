#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

function(FIND_VULKAN_EXT)

    if(NOT MDL_ENABLE_VULKAN_EXAMPLES)
        message(WARNING "Examples that require Vulkan are disabled. Enable the option 'MDL_ENABLE_VULKAN_EXAMPLES' and resolve the required dependencies to re-enable them.")
        return()
    endif()

    # if no specific Vulkan SDK is specified then try finding an installed SDK
    if(NOT VULKAN_SDK_DIR)
        set(VULKAN_SDK_DIR $ENV{VULKAN_SDK} CACHE PATH "")
    endif()

    if(WIN32)
        find_path(_VULKAN_INCLUDE
            NAMES vulkan/vulkan.h
            PATHS
                "${VULKAN_SDK_DIR}/Include"
            NO_DEFAULT_PATH
            )
        find_library(_VULKAN_LIB
            NAMES vulkan-1
            PATHS
                "${VULKAN_SDK_DIR}/Lib"
                "${VULKAN_SDK_DIR}/Bin"
            NO_DEFAULT_PATH
            )
        
        set(_VULKAN_BIN ${VULKAN_SDK_DIR}/Bin)
    else()
        find_path(_VULKAN_INCLUDE
            NAMES vulkan/vulkan.h
            PATHS
                "${VULKAN_SDK_DIR}/include"
            NO_DEFAULT_PATH
            )
        find_library(_VULKAN_LIB
            NAMES vulkan
            PATHS
                "${VULKAN_SDK_DIR}/lib"
            NO_DEFAULT_PATH
            )
    endif()

    # store paths that are later used in add_vulkan.cmake
    set(MDL_DEPENDENCY_VULKAN_INCLUDE ${_VULKAN_INCLUDE} CACHE INTERNAL "vulkan headers")
    set(MDL_DEPENDENCY_VULKAN_LIBS ${_VULKAN_LIB} CACHE INTERNAL "vulkan libs")
    if(WIN32)
        set(MDL_DEPENDENCY_VULKAN_BIN ${_VULKAN_BIN} CACHE INTERNAL "vulkan bin")
    endif()

    if(MDL_LOG_DEPENDENCIES)
        message(STATUS "[INFO] MDL_DEPENDENCY_VULKAN_INCLUDE:        ${MDL_DEPENDENCY_VULKAN_INCLUDE}")
        message(STATUS "[INFO] MDL_DEPENDENCY_VULKAN_LIBS:           ${MDL_DEPENDENCY_VULKAN_LIBS}")
        if(WIN32)
            message(STATUS "[INFO] MDL_DEPENDENCY_VULKAN_BIN:            ${MDL_DEPENDENCY_VULKAN_BIN}")
        endif()
    endif()
    #-----------------------------------------------------------------------------------------------


    # find the Khronos reference compiler glslang
    if(_VULKAN_INCLUDE)
        if(WIN32)
            set(_VULKAN_LIB_DIR "${VULKAN_SDK_DIR}/Lib")
        else()
            set(_VULKAN_LIB_DIR "${VULKAN_SDK_DIR}/lib")
        endif()

        # The previously found Vulkan SDK contains the glslang compiler
        set(_GLSLANG_INCLUDE ${Vulkan_INCLUDE_DIR})

        set(_GLSLANG_LIB
            "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glslang${CMAKE_STATIC_LIBRARY_SUFFIX}"
            "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV${CMAKE_STATIC_LIBRARY_SUFFIX}"
            "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Tools-opt${CMAKE_STATIC_LIBRARY_SUFFIX}"
            "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Tools${CMAKE_STATIC_LIBRARY_SUFFIX}"
            "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}MachineIndependent${CMAKE_STATIC_LIBRARY_SUFFIX}"
            "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}OSDependent${CMAKE_STATIC_LIBRARY_SUFFIX}"
            "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}OGLCompiler${CMAKE_STATIC_LIBRARY_SUFFIX}"
            "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}GenericCodeGen${CMAKE_STATIC_LIBRARY_SUFFIX}"
            )

        # Windows has debug versions
        if(WIN32)
            set(_GLSLANG_LIB_DEBUG
                "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glslangd${CMAKE_STATIC_LIBRARY_SUFFIX}"
                "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRVd${CMAKE_STATIC_LIBRARY_SUFFIX}"
                "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Tools-optd${CMAKE_STATIC_LIBRARY_SUFFIX}"
                "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Toolsd${CMAKE_STATIC_LIBRARY_SUFFIX}"
                "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}MachineIndependentd${CMAKE_STATIC_LIBRARY_SUFFIX}"
                "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}OSDependentd${CMAKE_STATIC_LIBRARY_SUFFIX}"
                "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}OGLCompilerd${CMAKE_STATIC_LIBRARY_SUFFIX}"
                "${_VULKAN_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}GenericCodeGend${CMAKE_STATIC_LIBRARY_SUFFIX}"
                )
        endif()
    endif()

    # store path that are later used in the add_vulkan.cmake
    set(MDL_DEPENDENCY_GLSLANG_INCLUDE ${_GLSLANG_INCLUDE} CACHE INTERNAL "glslang headers")
    set(MDL_DEPENDENCY_GLSLANG_LIBS ${_GLSLANG_LIB} CACHE INTERNAL "glslang libs")
    if(WIN32)
        set(MDL_DEPENDENCY_GLSLANG_LIBS_DEBUG ${_GLSLANG_LIB_DEBUG} CACHE INTERNAL "glslang libs")
    endif()

    if(MDL_LOG_DEPENDENCIES)
        message(STATUS "[INFO] MDL_DEPENDENCY_GLSLANG_INCLUDE:       ${MDL_DEPENDENCY_GLSLANG_INCLUDE}")
        message(STATUS "[INFO] MDL_DEPENDENCY_GLSLANG_LIBS:          ${MDL_DEPENDENCY_GLSLANG_LIBS}")
        if(WIN32)
            message(STATUS "[INFO] MDL_DEPENDENCY_GLSLANG_LIBS_DEBUG:    ${MDL_DEPENDENCY_GLSLANG_LIBS_DEBUG}")
        endif()
    endif()

endfunction()
