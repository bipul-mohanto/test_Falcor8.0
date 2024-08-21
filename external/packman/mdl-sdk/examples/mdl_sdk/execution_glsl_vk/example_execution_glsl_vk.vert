/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/

 // examples/mdl_sdk/execution_glsl_vk/example_execution_glsl_vk.vert

#version 450

layout(location = 0) out vec3 vPosition;
layout(location = 1) out vec3 vTexCoord;

void main()
{
    vec2 uv = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
    vPosition = vec3(uv * 2.0 - 1.0, 0.0);
    vTexCoord = vec3(uv, 0.0);
    gl_Position = vec4(vPosition, 1.0);
    
    // The y-axis needs to be inverted, since Vulkan uses to top-left corner for (0,0)
    // but the example expects the bottom-left corner to be the origin.
    gl_Position.y = -gl_Position.y;
}
