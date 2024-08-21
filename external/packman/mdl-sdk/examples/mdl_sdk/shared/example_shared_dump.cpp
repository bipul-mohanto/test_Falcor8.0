/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/

#include <iomanip>

#include "example_shared_dump.h"

namespace mi { namespace examples { namespace mdl {

// Utility function to dump the structure of a compiled material.
void dump_compiled_material(
    mi::neuraylib::ITransaction* transaction,
    mi::neuraylib::IMdl_factory* mdl_factory,
    const mi::neuraylib::ICompiled_material* cm,
    std::ostream& s)
{
    mi::base::Handle<mi::neuraylib::IValue_factory> value_factory(
        mdl_factory->create_value_factory( transaction));
    mi::base::Handle<mi::neuraylib::IExpression_factory> expression_factory(
        mdl_factory->create_expression_factory( transaction));

    mi::base::Uuid hash = cm->get_hash();
    char buffer[36];
    snprintf( buffer, sizeof( buffer),
        "%08x %08x %08x %08x", hash.m_id1, hash.m_id2, hash.m_id3, hash.m_id4);
    s << "    hash overall = " << buffer << std::endl;

    for( mi::Uint32 i = mi::neuraylib::SLOT_FIRST; i <= mi::neuraylib::SLOT_LAST; ++i) {
        hash = cm->get_slot_hash( mi::neuraylib::Material_slot( i));
        snprintf( buffer, sizeof( buffer),
            "%08x %08x %08x %08x", hash.m_id1, hash.m_id2, hash.m_id3, hash.m_id4);
        s << "    hash slot " << std::setw( 2) << i << " = " << buffer << std::endl;
    }

    mi::Size parameter_count = cm->get_parameter_count();
    for( mi::Size i = 0; i < parameter_count; ++i) {
        mi::base::Handle<const mi::neuraylib::IValue> argument( cm->get_argument( i));
        std::stringstream name;
        name << i;
        mi::base::Handle<const mi::IString> result(
            value_factory->dump( argument.get(), name.str().c_str(), 1));
        s << "    argument " << result->get_c_str() << std::endl;
    }

    mi::Size temporary_count = cm->get_temporary_count();
    for( mi::Size i = 0; i < temporary_count; ++i) {
        mi::base::Handle<const mi::neuraylib::IExpression> temporary( cm->get_temporary( i));
        std::stringstream name;
        name << i;
        mi::base::Handle<const mi::IString> result(
            expression_factory->dump( temporary.get(), name.str().c_str(), 1));
        s << "    temporary " << result->get_c_str() << std::endl;
    }

    mi::base::Handle<const mi::neuraylib::IExpression> body( cm->get_body());
    mi::base::Handle<const mi::IString> result( expression_factory->dump( body.get(), 0, 1));
    s << "    body " << result->get_c_str() << std::endl;

    s << std::endl;
}

}}}
