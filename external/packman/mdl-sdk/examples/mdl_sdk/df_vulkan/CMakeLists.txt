#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

# name of the target and the resulting example
set(PROJECT_NAME examples-mdl_sdk-df_vulkan)

# collect resources
set(PROJECT_RESOURCES
    mdl_runtime.glsl
    path_trace.comp
    display.vert
    display.frag
    )

# collect sources
set(PROJECT_SOURCES
    "example_df_vulkan.cpp"
    ${PROJECT_RESOURCES}
    )

# create target from template
create_from_base_preset(
    TARGET ${PROJECT_NAME}
    TYPE EXECUTABLE
    NAMESPACE mdl_sdk
    OUTPUT_NAME "df_vulkan"
    SOURCES ${PROJECT_SOURCES}
    EXAMPLE
)

# add dependencies
target_add_dependencies(TARGET ${PROJECT_NAME}
    DEPENDS
        vulkan
        glfw
        mdl::mdl_sdk
        mdl_sdk::shared
    )

# copy additional resources
target_copy_to_output_dir(TARGET ${PROJECT_NAME}
    RELATIVE    
        "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES       
        ${PROJECT_RESOURCES}
    )

# organize IDE folder
source_group("glsl" FILES ${PROJECT_RESOURCES})

# creates a user settings file to setup the debugger (visual studio only, otherwise this is a no-op)
target_create_vs_user_settings(TARGET ${PROJECT_NAME})

# -------------------------------------------------------------------------------------------------
# Create installation rules to copy the build directory
# -------------------------------------------------------------------------------------------------
add_target_install(
    TARGET ${PROJECT_NAME}
    DESTINATION "examples/mdl_sdk/df_vulkan"
    )

# -------------------------------------------------------------------------------------------------
# Add tests if available
# -------------------------------------------------------------------------------------------------
add_tests()
