#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

function(FIND_PANTORA_AXF_EXT)

    set(PANTORA_AXF_DIR "" CACHE PATH "Directory that contains the PANTORA_AXF include dir, libs and binaries")

    # this path has to be specified by the user
    if(NOT EXISTS ${PANTORA_AXF_DIR})
        message(FATAL_ERROR "The dependency \"Pantora AXF\" could not be resolved. Please specify 'PANTORA_AXF_DIR' or disable 'MDL_ENABLE_AXF_EXAMPLES'")
        return()
    endif()

    # assuming that the binaries are downloaded from ____
    set(_PANTORA_AXF_INCLUDE "${PANTORA_AXF_DIR}/../include")
    if(WINDOWS)
        set(_PANTORA_AXF_SHARED "${PANTORA_AXF_DIR}/bin/AxFDecoding.1.8.1.dll")
        set(_PANTORA_AXF_LIBS "${PANTORA_AXF_DIR}/lib/AxFDecoding.lib")
    elseif(LINUX)
        set(_PANTORA_AXF_SHARED "${PANTORA_AXF_DIR}/lib/libAxFDecoding.so.1.8.1")
        set(_PANTORA_AXF_LIBS "${PANTORA_AXF_DIR}/lib/libAxFDecoding.so.1.8.1")
    elseif(MACOSX)
        set(_PANTORA_AXF_SHARED "${PANTORA_AXF_DIR}/lib/libAxFDecoding.1.8.1.dylib")
        set(_PANTORA_AXF_LIBS "${PANTORA_AXF_DIR}/lib/libAxFDecoding.1.8.1.dylib")
    endif()
    foreach(_SHARED ${_PANTORA_AXF_SHARED})
        if(NOT EXISTS ${_SHARED})
            message(FATAL_ERROR "The dependency \"Pantora AXF\" could not be resolved. The following library does not exist: \"${_SHARED}\". To continue without AFX, you can disable the option 'MDL_ENABLE_AXF_EXAMPLES'.")
        endif()
    endforeach()
    foreach(_LIB ${_PANTORA_AXF_LIBS})
        if(NOT EXISTS ${_LIB})
            message(FATAL_ERROR "The dependency \"Pantora AXF\" could not be resolved. The following library does not exist: \"${_LIB}\". To continue without AFX, you can disable the option 'MDL_ENABLE_AXF_EXAMPLES'.")
        endif()
    endforeach()

    # store path that are later used
    set(MDL_DEPENDENCY_PANTORA_AXF_INCLUDE ${_PANTORA_AXF_INCLUDE} CACHE INTERNAL "PANTORA_AXF includes")
    set(MDL_DEPENDENCY_PANTORA_AXF_LIBS ${_PANTORA_AXF_LIBS} CACHE INTERNAL "PANTORA_AXF static libs")
    set(MDL_DEPENDENCY_PANTORA_AXF_SHARED ${_PANTORA_AXF_SHARED} CACHE INTERNAL "PANTORA_AXF shared libs")
    set(MDL_PANTORA_AXF_FOUND ON CACHE INTERNAL "")

    if(MDL_LOG_DEPENDENCIES)
        message(STATUS "[INFO] MDL_DEPENDENCY_PANTORA_AXF_SHARED:    ${MDL_DEPENDENCY_PANTORA_AXF_SHARED}")
    endif()

endfunction()
