/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_module_transformer.h
/// \brief Interfaces for transforming MDL modules
#ifndef MDL_MDL_MODULE_TRANSFORMER
#define MDL_MDL_MODULE_TRANSFORMER 1

#include <mi/base/iinterface.h>
#include <mi/base/interface_declare.h>
#include <mi/mdl/mdl_iowned.h>
#include <mi/mdl/mdl_messages.h>

namespace mi {
namespace mdl {

class IModule;

/// This interface gives access to the MDL module transformer.
class IMDL_module_transformer : public
    mi::base::Interface_declare<0x2c8f478e,0xfecd,0x443b,0xa8,0x2c,0xb9,0x9a,0x5f,0xc9,0x05,0xf4,
    mi::base::IInterface>
{
public:
    /// Inline all imports of a module, creating a new one.
    ///
    /// \param module       the module
    ///
    /// This function inlines ALL except standard library imports and produces a new module.
    /// The imported functions, materials, and types are renamed and only exported if visible
    /// in the interface.
    ///
    /// The annotation "origin(string)" holds the original full qualified name.
    ///
    /// Returns the argument if no changes are required.
    virtual IModule const *inline_imports(IModule const *module) = 0;

    /// Inline all imports of a module, creating a new one.
    ///
    /// \param module       the module
    ///
    /// This function inlines ALL except standard library imports and produces a new module.
    /// The imported functions, materials, and types are renamed and only exported if visible
    /// in the interface.
    ///
    /// The annotation "origin(string)" holds the original full qualified name.
    ///
    /// Returns the argument if no changes are required.
    virtual IModule *inline_imports(IModule *module) = 0;

    /// Inline all MDLE imports of a module, creating a new one.
    ///
    /// \param module       the module
    ///
    /// This function inlines ALL MDLE imports and produces a new module.
    /// The imported functions, materials, and types are renamed and only exported if visible
    /// in the interface.
    ///
    /// The annotation "origin(string)" holds the original full qualified name.
    ///
    /// Returns the argument if no changes are required.
    virtual IModule const *inline_mdle(IModule const *module) = 0;

    /// Inline all MDLE imports of a module, creating a new one.
    ///
    /// \param module       the module
    ///
    /// This function inlines ALL MDLE imports and produces a new module.
    /// The imported functions, materials, and types are renamed and only exported if visible
    /// in the interface.
    ///
    /// The annotation "origin(string)" holds the original full qualified name.
    ///
    /// Returns the argument if no changes are required.
    virtual IModule *inline_mdle(IModule *module) = 0;

    /// Access messages of the last operation.
    virtual Messages const &access_messages() const = 0;
};

}  // mdl
}  // mi

#endif // MDL_MDL_MODULE_TRANSFORMER
