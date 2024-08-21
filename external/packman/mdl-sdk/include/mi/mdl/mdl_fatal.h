/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_fatal.h
/// \brief Interfaces for handling fatal errors in the MDL core compiler
#ifndef MDL_FATAL_H
#define MDL_FATAL_H 1

namespace mi {
namespace mdl {

/// A simple helper interface handling fatal compiler errors.
///
/// This interface must be implemented by the user application.
class IFatal_error {
public:
    /// Called when the compiler detects a fatal unrecoverable error.
    ///
    /// \param msg  the error massage
    ///
    /// Normally the application will abort.
    virtual void fatal(
        char const *msg) = 0;
};

}  // mdl
}  // mi

#endif
