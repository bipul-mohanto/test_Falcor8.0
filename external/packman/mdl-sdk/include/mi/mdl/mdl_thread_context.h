/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_thread_context.h
/// \brief Interfaces to handle thread contextes in MDL Core
#ifndef MDL_THREAD_CONTEXT_H
#define MDL_THREAD_CONTEXT_H 1

#include <mi/base/iinterface.h>
#include <mi/base/interface_declare.h>

namespace mi {
namespace mdl {

class Messages;
class Options;

/// An interface for handling different thread contexts inside the MDL compiler.
///
/// When the compiler is used from different threads, every thread should have its own
/// context. If no context is provided, the compiler automatically creates one.
class IThread_context : public
    mi::base::Interface_declare<0x98779789,0x92bc,0x4530,0x8b,0xfd,0xc3,0xb2,0xfc,0x1e,0xb7,0x8d,
    mi::base::IInterface>
{
public:
    /// Access compiler messages of last operation that used this context.
    ///
    /// \note When compiling a module, error message are also copied
    ///       into the IModule if one was created.
    virtual Messages const &access_messages() const = 0;

    /// Access compiler options for the next invocation.
    ///
    /// Get access to the MDL compiler options, \see mdl_compiler_options.
    ///
    /// \note Options set in the thread context will overwrite options set on the compiler
    ///       directly but are not persistent, i.e. only valid during the time this thread
    ///       context is in use.
    ///
    virtual Options const &access_options() const = 0;

    /// Access compiler options for the next invocation.
    ///
    /// Get access to the MDL compiler options, \see mdl_compiler_options.
    ///
    /// \note Options set in the thread context will overwrite options set on the compiler
    ///       directly but are not persistent, i.e. only valid during the time this thread
    ///       context is in use.
    ///
    virtual Options &access_options() = 0;
};

}  // mdl
}  // mi

#endif
