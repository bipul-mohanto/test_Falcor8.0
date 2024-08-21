/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/

// examples/mdl_sdk/df_vulkan/display.frag

#version 450

layout(location = 0) out vec4 FragColor;

layout(rgba32f, set = 0, binding = 0) uniform readonly restrict image2D uBeautyBuffer;
layout(rgba32f, set = 0, binding = 1) uniform readonly restrict image2D uAuxAlbedoBuffer;
layout(rgba32f, set = 0, binding = 2) uniform readonly restrict image2D uAuxNormalBuffer;

layout(push_constant) uniform UserData
{
    uint uBufferIndex;
};

void main()
{
    ivec2 uv = ivec2(gl_FragCoord.xy);

    // Flip image because Vulkan uses the bottom-left corner as the origin,
    // but the rendering code assumed the origin to be the top-left corner.
    uv.y = imageSize(uBeautyBuffer).y - uv.y - 1;

    vec3 color;
    switch (uBufferIndex)
    {
    case 1:
        color = imageLoad(uAuxAlbedoBuffer, uv).xyz;
        break;

    case 2:
        color = imageLoad(uAuxNormalBuffer, uv).xyz;
        if (dot(color, color) > 0.01)
            color = normalize(color) * 0.5 + 0.5;
        break;

    default:
        color = imageLoad(uBeautyBuffer, uv).xyz;
        break;
    }

    // Apply reinhard tone mapping
    const float burn_out = 0.1;
    color *= (vec3(1.0) + color * burn_out) / (vec3(1.0) + color);

    // Apply gamma correction
    color = pow(clamp(color, 0.0, 1.0), vec3(1.0 / 2.2));

    FragColor = vec4(color, 1.0);
}
