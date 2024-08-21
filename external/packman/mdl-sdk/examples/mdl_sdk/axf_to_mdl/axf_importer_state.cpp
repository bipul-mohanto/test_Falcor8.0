/***************************************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 **************************************************************************************************/

/// \file
/// \brief Our own state adaption.

#include "axf_importer_state.h"

#include <AxF/decoding/AxF_basic_io.h>

namespace mi {
namespace examples {
namespace impaxf {

using namespace std;

void Axf_impexp_state::init(
    const string& i_url)
{

}

const char* Axf_impexp_state::get_uri() const
{
    return m_url.c_str();
}

const char* Axf_impexp_state::get_prefix() const
{
    if (m_name_space.empty())
        return 0;
    else
        return m_name_space.c_str();
}

mi::Uint32 Axf_impexp_state::get_line_number() const
{
    return m_line_number;
}

void Axf_impexp_state::set_line_number(
    mi::Uint32 n)
{
    m_line_number = n;
}

void Axf_impexp_state::incr_line_number()
{
    ++m_line_number;
}

void Axf_impexp_state::parse_importer_options(
    const mi::IMap* importer_options)
{
    m_axf_color_space = AXF_COLORSPACE_LINEAR_SRGB_E; // if no color space is set, use default
    m_axf_module_prefix = "axf";
    m_color_rep = COLOR_REP_ALL;
    
    if( !importer_options)
        return;

    if (importer_options->has_key( "prefix")) {
        mi::base::Handle<const mi::IString> option(
            importer_options->get_value<mi::IString>( "prefix"));
        if (option.is_valid_interface())
            m_name_space = option->get_c_str();
    }    

    if (importer_options->has_key( "list_elements")) {
        mi::base::Handle<const mi::IBoolean> option(
            importer_options->get_value<mi::IBoolean>( "list_elements"));
        if (option.is_valid_interface())
            m_element_list_flag = option->get_value<bool>();
    }

    if (importer_options->has_key( "axf_color_space")) {
        mi::base::Handle<const mi::IString> option(
            importer_options->get_value<mi::IString>( "axf_color_space"));
        if (option.is_valid_interface())
            m_axf_color_space = option->get_c_str();
        else
            m_axf_color_space.clear(); // to trigger warning in import (which then uses default)
    }

    if (importer_options->has_key( "axf_module_prefix")) {
        mi::base::Handle<const mi::IString> option(
            importer_options->get_value<mi::IString>( "axf_module_prefix"));
        if (option.is_valid_interface())
            m_axf_module_prefix = option->get_c_str();
    }

    if (importer_options->has_key( "axf_color_representation")) {
        mi::base::Handle<const mi::IString> option(
            importer_options->get_value<mi::IString>( "axf_color_representation"));
        if (option.is_valid_interface()) {
            const char *s = option->get_c_str();
            if (strcmp(s, "rgb") == 0) {
                m_color_rep = COLOR_REP_RGB;
            } else if (strcmp(s, "spectral") == 0) {
                m_color_rep = COLOR_REP_SPECTRAL;
            } else if (strcmp(s, "all") == 0) {
                m_color_rep = COLOR_REP_ALL;
            }
            //!! TODO: error reporting
        }
    }
}

void Axf_impexp_state::parse_importer_options(
    const Axf_importer_options &importer_options)
{
    m_mdl_output_filename = importer_options.mdl_output_filename;
    m_axf_module_prefix = importer_options.axf_module_prefix;
    m_axf_color_space = importer_options.axf_color_space;

    const char* s = importer_options.axf_color_representation.c_str();
    if (strcmp(s, "rgb") == 0) {
        m_color_rep = COLOR_REP_RGB;
    }
    else if (strcmp(s, "spectral") == 0) {
        m_color_rep = COLOR_REP_SPECTRAL;
    }
    else if (strcmp(s, "all") == 0) {
        m_color_rep = COLOR_REP_ALL;
    }
}


mi::IMap* Axf_impexp_state::create_importer_options(
    mi::neuraylib::ITransaction* transaction) const
{
    mi::base::Handle<mi::IString> prefix( transaction->create<mi::IString>( "String"));
    prefix->set_c_str( get_prefix());

    mi::base::Handle<mi::IBoolean> list_elements( transaction->create<mi::IBoolean>( "Boolean"));
    list_elements->set_value( get_element_list_flag());

    mi::IMap* importer_options = transaction->create<mi::IMap>( "Map<Interface>");
    importer_options->insert( "prefix", prefix.get());
    importer_options->insert( "list_elements", list_elements.get());
    return importer_options;
}

}
}
}