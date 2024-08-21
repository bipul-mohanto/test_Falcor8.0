/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl.h
/// \brief MDL Core main header, includes all other headers and declares the main factory function.
#ifndef MDL_H
#define MDL_H 1

#include <mi/base/version.h>
#include <mi/base/types.h>
#include <mi/base/iinterface.h>
#include <mi/base/interface_declare.h>

#include <mi/mdl/mdl_annotations.h>
#include <mi/mdl/mdl_archiver.h>
#include <mi/mdl/mdl_assert.h>
#include <mi/mdl/mdl_code_generators.h>
#include <mi/mdl/mdl_comparator.h>
#include <mi/mdl/mdl_declarations.h>
#include <mi/mdl/mdl_definitions.h>
#include <mi/mdl/mdl_entity_resolver.h>
#include <mi/mdl/mdl_expressions.h>
#include <mi/mdl/mdl_fatal.h>
#include <mi/mdl/mdl_generated_code.h>
#include <mi/mdl/mdl_generated_dag.h>
#include <mi/mdl/mdl_generated_executable.h>
#include <mi/mdl/mdl_iowned.h>
#include <mi/mdl/mdl_mdl.h>
#include <mi/mdl/mdl_messages.h>
#include <mi/mdl/mdl_modules.h>
#include <mi/mdl/mdl_names.h>
#include <mi/mdl/mdl_options.h>
#include <mi/mdl/mdl_positions.h>
#include <mi/mdl/mdl_printers.h>
#include <mi/mdl/mdl_serializer.h>
#include <mi/mdl/mdl_statements.h>
#include <mi/mdl/mdl_stdlib_types.h>
#include <mi/mdl/mdl_streams.h>
#include <mi/mdl/mdl_symbols.h>
#include <mi/mdl/mdl_thread_context.h>
#include <mi/mdl/mdl_types.h>
#include <mi/mdl/mdl_values.h>

#if MI_BASE_VERSION_MAJOR != 1
#error "MI_BASE_VERSION_MAJOR is not equal 1, but 1 is required for MDL headers."
#endif

#ifdef MI_PLATFORM_WINDOWS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

//-----------------------------------------------------------------------------
// Initialize MDL Core
//

extern "C" {

/// Initializes the MDL Core library and obtains the primary MDL interface.
/// This function is the entry point to using the MDL Core API.
///
/// \param alloc  If non-NULL, an allocator interface that will be used for all
///               memory allocations in this compiler.
///               If NULL, a malloc-based allocator will be used.
///
/// \returns    A pointer to the primary MDL interface.
DLL_EXPORT mi::mdl::IMDL *mi_mdl_factory(mi::base::IAllocator *alloc);

} // extern "C"

namespace mi {
/// Common namespace for MDL Core APIs of NVIDIA Advanced Rendering Center GmbH.
namespace mdl {
}  // mdl
}  // mi

#endif // MDL_H
