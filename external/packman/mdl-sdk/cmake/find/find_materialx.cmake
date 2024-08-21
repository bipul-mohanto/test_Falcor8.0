#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

function(FIND_MATERIALX)

    set(MATERIALX_DIR "NOT-SPECIFIED" CACHE PATH "Path to a downloaded and extracted MaterialX pre-built package.")

    # check if the dependencies are available, if not disable
    #-----------------------------------------------------------------------------------------------
    if(NOT EXISTS ${MATERIALX_DIR})
        message(FATAL_ERROR "The dependency \"MaterialX\" could not be resolved. Please specify 'MATERIALX_DIR' or disable 'MDL_ENABLE_MATERIALX'")
        return()
    endif()

    # collect information required for the build
    #-----------------------------------------------------------------------------------------------

    # set include dir
    set(_MX_INCLUDE ${MATERIALX_DIR}/include)
    
    # set libs
    set(_MX_LIBS
        ${MATERIALX_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}MaterialXCore$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${MATERIALX_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}MaterialXFormat$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${MATERIALX_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}MaterialXGenShader$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${MATERIALX_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}MaterialXGenMdl$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
    )
    
    # store path that are later used in the add_materialx.cmake
    set(MDL_DEPENDENCY_MATERIALX_INCLUDE ${_MX_INCLUDE} CACHE INTERNAL "materialx headers" FORCE)
    set(MDL_DEPENDENCY_MATERIALX_LIBS ${_MX_LIBS} CACHE INTERNAL "materialx libs" FORCE)
  
    if(MDL_LOG_DEPENDENCIES)
        message(STATUS "[INFO] MDL_DEPENDENCY_MATERIALX_INCLUDE:     ${MDL_DEPENDENCY_MATERIALX_INCLUDE}")
        message(STATUS "[INFO] MDL_DEPENDENCY_MATERIALX_LIBS:        ${MDL_DEPENDENCY_MATERIALX_LIBS}")
    endif()

endfunction()
