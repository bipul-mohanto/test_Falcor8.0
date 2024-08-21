/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/

// examples/mdl_sdk/shared/example_shared_dump.h
//
// Code shared by all examples that dump a compiled material instance.

#ifndef EXAMPLE_SHARED_DUMP_H
#define EXAMPLE_SHARED_DUMP_H

#include "utils/mdl.h"

namespace mi { namespace examples { namespace mdl {

void dump_compiled_material(
    mi::neuraylib::ITransaction* transaction,
    mi::neuraylib::IMdl_factory* mdl_factory,
    const mi::neuraylib::ICompiled_material* cm,
    std::ostream& s);

}}}

#endif // MI_EXAMPLE_SHARED_DUMP_H
