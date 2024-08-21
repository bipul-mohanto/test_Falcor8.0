/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_stdlib_types.h
/// \brief Predefined enum types from the MDL standard library
#ifndef MDL_STDLIB_TYPES_H
#define MDL_STDLIB_TYPES_H 1

namespace mi {
namespace mdl {

/// This namespace contains enum types that mimics MDL predefined enum types.
namespace stdlib {

/// The MDL tex::gamma_mode enum.
enum Tex_gamma_mode {
    gamma_default = 0,
    gamma_linear  = 1,
    gamma_srgb    = 2
};

/// The tex::wrap_mode enum.
enum Tex_wrap_mode {
    wrap_clamp           = 0,
    wrap_repeat          = 1,
    wrap_mirrored_repeat = 2,
    wrap_clip            = 3
};

/// MBSDFs can consist of two parts, which can be selected using this enumeration.
enum Mbsdf_part
{
    mbsdf_data_reflection = 0,
    mbsdf_data_transmission = 1
};

} // stdlib
} // mdl
} // mi

#endif
