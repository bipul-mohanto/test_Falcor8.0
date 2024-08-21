/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_assert.h
/// \brief Interfaces for forwarding MDL Core assertions
#ifndef MDL_ASSERT_H
#define MDL_ASSERT_H 1

namespace mi {
namespace mdl {

/// A simple assert helper interface.
class IAsserter {
public:
    /// Called by a failed MDL_ASSERT.
    ///
    /// \param expr  the expression that failed
    /// \param file  the name of the file that contains the failing expression
    /// \param line  the line number of the failing expression
    virtual void assertfailed(
        char const   *expr,
        char const   *file,
        unsigned int line) = 0;
};

}  // mdl
}  // mi

#endif
