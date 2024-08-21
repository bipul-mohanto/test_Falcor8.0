/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/

// examples/mdl_sdk/execution_glsl_vk/example_execution_glsl_vk.frag
//
// This file contains the implementations of the texture access functions
// and the fragment shader used to evaluate the material sub-expressions.

layout(push_constant) uniform User_data
{
    // Material pattern as chosen by the user.
    uint material_pattern;

    // Current time in seconds since the start of the render loop.
    float animation_time;
} user_data;

// Array containing all 2D texture samplers of all used materials.
layout(set = 0, binding = 0) uniform sampler2D material_texture_samplers_2d[NUM_TEXTURES];


// The input variables coming from the vertex shader.
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vTexCoord;


// The color output variable of this fragment shader.
layout(location = 0) out vec4 FragColor;


// The MDL material state structure as configured via the GLSL backend options.
// Note: Must be in sync with the state struct in generate_glsl_switch_func and the code generated
//       by the MDL SDK (see dumped code when enabling DUMP_GLSL in example_execution_glsl_vk.cpp).
struct State
{
    vec3 normal;
    vec3 geom_normal;
    vec3 position;
    float animation_time;
    vec3 text_coords[1];
    vec3 tangent_u[1];
    vec3 tangent_v[1];
    int ro_data_segment_offset;
    mat4 world_to_object;
    mat4 object_to_world;
    int object_id;
    float meters_per_scene_unit;
    int arg_block_offset;
};


//
// The prototypes of the functions generated in our generate_glsl_switch_func() function.
//

// Return the number of available MDL material subexpressions.
uint get_mdl_num_mat_subexprs();

// Return the result of the MDL material subexpression given by the id.
vec3 mdl_mat_subexpr(uint id, State state);


// Implementation of tex::lookup_*() for a texture_2d texture.
vec4 tex_lookup_float4_2d(
    int tex, vec2 coord, int wrap_u, int wrap_v, vec2 crop_u, vec2 crop_v, float frame)
{
    if (tex == 0) return vec4(0);
    return texture(material_texture_samplers_2d[tex - 1], coord);
}

// Implementation of tex::texel_*() for a texture_2d texture.
vec4 tex_texel_2d(int tex, ivec2 coord, ivec2 uv_tile)
{
    if (tex == 0) return vec4(0);
    return texelFetch(material_texture_samplers_2d[tex - 1], coord, 0);
}


// The fragment shader main function evaluating the MDL sub-expression.
void main()
{
    // Set number of materials to use according to selected pattern
    uint num_materials = bitCount(user_data.material_pattern);

    // Assign materials in a checkerboard pattern
    uint material_index =
        (uint(vTexCoord.x * 4) ^ uint(vTexCoord.y * 4)) % num_materials;

    // Change material index according to selected pattern
    switch (user_data.material_pattern)
    {
        case 2u: material_index = 1u; break;
        case 4u: material_index = 2u; break;
        case 5u: if (material_index == 1u) material_index = 2u; break;
        case 6u: material_index += 1u; break;
    }
    if (material_index > get_mdl_num_mat_subexprs())
        material_index = get_mdl_num_mat_subexprs();

    // Set MDL material state for state functions in "field" mode
    State state = State(
        /*normal=*/                 vec3(0.0, 0.0, 1.0),
        /*geometry_normal=*/        vec3(0.0, 0.0, 1.0),
        /*position=*/               -vPosition,
        /*animation_time=*/         user_data.animation_time,
        /*text_coords=*/            vec3[1](vTexCoord),
        /*texture_tangent_u=*/      vec3[1](vec3(1.0, 0.0, 0.0)),
        /*texture_tangent_v=*/      vec3[1](vec3(0.0, 1.0, 0.0)),
        /*ro_data_segment_offset=*/ 0,
        /*world_to_object=*/        mat4(1.0),
        /*object_to_world=*/        mat4(1.0),
        /*object_id=*/              0,
        /*meters_per_scene_unit=*/  1.0,
        /*arg_block_offset=*/       0
    );

    // Evaluate material sub-expression
    vec3 res = mdl_mat_subexpr(material_index, state);

    // Apply gamma correction and write to output variable
    FragColor = pow(vec4(res, 1.0), vec4(1.0 / 2.2));
}
