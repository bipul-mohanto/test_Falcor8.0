/***************************************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 **************************************************************************************************/
/// \file
/// \brief API component representing the MDL compiler

#ifndef MI_NEURAYLIB_IMDL_COMPILER_H
#define MI_NEURAYLIB_IMDL_COMPILER_H

#include <mi/base/interface_declare.h>

namespace mi {

namespace neuraylib {

/** \addtogroup mi_neuray_mdl_compiler
@{
*/

/// The MDL compiler allows to register builtin modules.
class IMdl_compiler : public
    mi::base::Interface_declare<0x8fff0a2d,0x7df7,0x4552,0x92,0xf7,0x36,0x1d,0x31,0xc6,0x30,0x08>
{
public:

    /// Adds a builtin MDL module.
    ///
    /// Builtin modules allow to use the \c native() annotation which is not possible for regular
    /// modules. Builtin modules can only be added before the first regular module has been loaded.
    ///
    /// \note After adding a builtin module it is still necessary to load it using
    ///       #mi::neuraylib::IMdl_impexp_api::load_module() before it can actually be used.
    ///
    /// \param module_name     The MDL name of the module.
    /// \param module_source   The MDL source code of the module.
    /// \return
    ///                        -  0: Success.
    ///                        - -1: Possible failure reasons: invalid parameters (\c NULL pointer),
    ///                              \p module_name is not a valid module name, failure to compile
    ///                              the module, or a regular module has already been loaded.
    virtual Sint32 add_builtin_module( const char* module_name, const char* module_source) = 0;
};

/**@}*/ // end group mi_neuray_mdl_compiler

} // namespace neuraylib

} // namespace mi

#endif // MI_NEURAYLIB_IMDL_COMPILER_H
