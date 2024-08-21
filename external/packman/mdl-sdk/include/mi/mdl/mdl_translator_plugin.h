/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_translator_plugin.h
/// \brief Interfaces for the MDL core compiler translator plugin.
#ifndef MDL_TRANSLATOR_PLUGIN_H
#define MDL_TRANSLATOR_PLUGIN_H 1

#include <mi/base/interface_declare.h>

namespace mi {
namespace mdl {

class IModule;
class IModule_cache;
class IThread_context;

/// An interface handling transparent conversions of foreign modules to MDL.
class IMDL_foreign_module_translator : public
    mi::base::Interface_declare<0x02713b54,0x6aac,0x4721,0x8f,0x52,0xbc,0xfe,0xa3,0x25,0xaf,0x1e,
    mi::base::IInterface>
{
public:
    /// Returns true if the given fully absolute MDL module name is a foreign module.
    ///
    /// \param module_name  an absolute MDL module name
    virtual bool is_foreign_module(char const *module_name) = 0;

    /// Translate a foreign module into a MDL module.
    ///
    /// \param ctx          the current thread context
    /// \param module_name  an absolute MDL module name
    /// \param cache        the current module cache
    ///
    /// \return the translated MDL module
    virtual IModule const *compile_foreign_module(
        IThread_context *ctx,
        char const      *module_name,
        IModule_cache   *cache) = 0;

    /// If this translator puts converted modules into a virtual root package, return its name.
    virtual char const *get_virtual_root_package() const = 0;
};

} // mdl
} // mi

#endif // MDL_TRANSLATOR_PLUGIN_H
