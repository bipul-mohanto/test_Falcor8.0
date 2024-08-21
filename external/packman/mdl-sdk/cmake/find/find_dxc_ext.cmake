#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

function(FIND_DXC_EXT)

    set(DXC_DIR "" CACHE PATH "Directory that contains the DXC include dir, libs and binaries")

    # this path has to be specified by the user
    if(NOT EXISTS ${DXC_DIR})
        message(FATAL_ERROR "The dependency \"DirectX Shader Compiler\" could not be resolved. Please specify 'DXC_DIR' or disable 'MDL_ENABLE_D3D12_EXAMPLES'")
        return()
    endif()

    # assuming that the windows (x64) binaries from https://github.com/microsoft/DirectXShaderCompiler/releases are used
    if(WINDOWS)
        set(_DXC_INCLUDE "${DXC_DIR}/inc")
        set(_DXC_LIBS "${DXC_DIR}/lib/x64/dxcompiler.lib")
        set(_DXC_SHARED "${DXC_DIR}/bin/x64/dxcompiler.dll"
                        "${DXC_DIR}/bin/x64/dxil.dll"
        )
    endif()
    foreach(_SHARED ${_DXC_INCLUDE} ${_DXC_SHARED}   ${MDL_DEPENDENCY_DXC_LIBS})
        if(NOT EXISTS ${_SHARED})
            message(FATAL_ERROR "The dependency \"DirectX Shader Compiler\" could not be resolved. The following library does not exist: \"${_SHARED}\". To continue without D3D12, you can disable the option 'MDL_ENABLE_D3D12_EXAMPLES'.")
        endif()
    endforeach()

    # store path that are later used
    set(MDL_DEPENDENCY_DXC_INCLUDE ${_DXC_INCLUDE} CACHE INTERNAL "DXC includes")
    set(MDL_DEPENDENCY_DXC_SHARED ${_DXC_SHARED} CACHE INTERNAL "DXC shared libs")
    set(MDL_DEPENDENCY_DXC_LIBS ${_DXC_LIBS} CACHE INTERNAL "DXC libs")
    set(MDL_DXC_FOUND ON CACHE INTERNAL "")

    if(MDL_LOG_DEPENDENCIES)
        message(STATUS "[INFO] MDL_DEPENDENCY_DXC_INCLUDE:           ${MDL_DEPENDENCY_DXC_INCLUDE}")
        message(STATUS "[INFO] MDL_DEPENDENCY_DXC_LIBS:              ${MDL_DEPENDENCY_DXC_LIBS}")
        message(STATUS "[INFO] MDL_DEPENDENCY_DXC_SHARED:            ${MDL_DEPENDENCY_DXC_SHARED}")
    endif()

endfunction()
