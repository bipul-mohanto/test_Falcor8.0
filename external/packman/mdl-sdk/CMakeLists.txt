#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# policies
if(POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif()
if(POLICY CMP0102)
    cmake_policy(SET CMP0102 NEW)
endif()

set(MDL_BASE_FOLDER ${CMAKE_SOURCE_DIR} CACHE PATH "The folder that contains the targets to build and the cmake utility scripts.")
set(MDL_INCLUDE_FOLDER ${CMAKE_SOURCE_DIR}/include CACHE PATH "The folder that interface headers of the MDL-SDK, i.e., mi/base, mi/neuray, ... directories.")
set(MDL_SRC_FOLDER ${CMAKE_SOURCE_DIR} CACHE INTERNAL "In the MDL Binaray Release, this is equal to the 'CMAKE_SOURCE_DIR'.")
set(MDL_EXAMPLES_FOLDER ${CMAKE_SOURCE_DIR}/examples CACHE PATH "The folder that contains the mdl examples")
set(MDL_BUILD_SDK_EXAMPLES ON CACHE INTERNAL "")

# default values for internal builds, before project()
if(EXISTS ${MDL_BASE_FOLDER}/CMakeInternalBuildConfig_Toolchain_File.cmake AND NOT MDL_USE_LOCAL_DEPENDENCIES)
   include(${MDL_BASE_FOLDER}/CMakeInternalBuildConfig_Toolchain_File.cmake)
endif()

# before project() due to its use in CMAKE_TOOLCHAIN_FILE
if(WIN32 AND NOT UNIX)
    set(VCPKG_TARGET_TRIPLET x64-windows-static)
endif()

project(mdl-examples LANGUAGES C CXX)

# default values for internal builds, after project()
if(EXISTS ${MDL_BASE_FOLDER}/CMakeInternalBuildConfig.cmake AND NOT MDL_USE_LOCAL_DEPENDENCIES)
   include(${MDL_BASE_FOLDER}/CMakeInternalBuildConfig.cmake)
endif()

#--------------------------------------------------------------------------------------------------
# configuration options
option(MDL_BUILD_ARNOLD_PLUGIN "Enable the build of the MDL Arnold plugin." OFF)
option(MDL_LOG_PLATFORM_INFOS "Prints some infos about the current build system (relevant for error reports)." ON)
option(MDL_LOG_DEPENDENCIES "Prints the list of dependencies during the generation step." ON)
option(MDL_LOG_FILE_DEPENDENCIES "Prints the list of files that is copied after a successful build." OFF)
# This option does not really have an effect since the dependencies exist
# already as binaries anyway. Exists mostly for consistency and to ensure the
# value is defined.
option(MDL_TREAT_RUNTIME_DEPS_AS_BUILD_DEPS "Treat runtime dependencies as build dependencies." ON)
set(MDL_ADDITIONAL_COMPILER_DEFINES "MDL_BINARY_RELEASE" CACHE STRING "Additional compile defines that are passed to each of the projects")
set(MDL_ADDITIONAL_COMPILER_OPTIONS "" CACHE STRING "Additional compile options that are passed to each of the projects")

# set the default installation path
if(NOT DEFINED CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "..." FORCE)
endif()

# -------------------------------------------------------------------------------------------------
# general setup
include(${MDL_BASE_FOLDER}/cmake/setup.cmake)

if(MDL_LOG_PLATFORM_INFOS)
    MESSAGE(STATUS "[INFO] MDL_BUILD_ARNOLD_PLUGIN:              ${MDL_BUILD_ARNOLD_PLUGIN}")
endif()

# presets and utility functions used in all CMakeLists
include(${MDL_BASE_FOLDER}/cmake/utilities.cmake)

#--------------------------------------------------------------------------------------------------
# list of modules in defined order

# third party
add_subdirectory(${MDL_EXAMPLES_FOLDER}/thirdparty/imgui)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/thirdparty/tinyxml2)

# MDL SDK Examples
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/shared)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/archives)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/calls)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/code_gen)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/compilation)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/create_module)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/discovery)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/distilling)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/distilling_target)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/execution_native)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/generate_mdl_identifier)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/instantiation)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/mdle)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/modules)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/start_shutdown)
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/traversal)

if(MDL_ENABLE_OPENGL_EXAMPLES)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/df_native)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/distilling_glsl)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/execution_glsl)
endif()

if(MDL_ENABLE_VULKAN_EXAMPLES)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/execution_glsl_vk)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/df_vulkan)
endif()

if(MDL_ENABLE_CUDA_EXAMPLES)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/distilling_unity)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/execution_cuda)
    if(MDL_ENABLE_OPENGL_EXAMPLES)
        add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/df_cuda)
        if(MDL_ENABLE_OPTIX7_EXAMPLES)
            if(WINDOWS)
                add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/optix7)
            else()
                message(WARNING "The OptiX 7 example is currently only available for Windows.")
            endif()
        endif()
    endif()
endif()

if(WINDOWS AND MDL_ENABLE_D3D12_EXAMPLES)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/dxr)
endif()

if(MDL_ENABLE_QT_EXAMPLES)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/mdl_browser)
endif()

if(MDL_ENABLE_AXF_EXAMPLES AND ARCH_X64)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/axf_to_mdl)
endif()

# Example Content
add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl)

if(MDL_BUILD_ARNOLD_PLUGIN)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_sdk/mdl_arnold)
endif()

# Language Bindings
if(MDL_ENABLE_PYTHON_BINDINGS)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/../bindings/mdl_python)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_python)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_python/create_expression_graph)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_python/modules)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_python/pymdl_inspection)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_python/start_shutdown)
    add_subdirectory(${MDL_EXAMPLES_FOLDER}/mdl_python/tests)
endif()
