/***************************************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 **************************************************************************************************/

 /// \file
 /// \brief The .axf importer options.

#ifndef EXAMPLE_AXF_TO_MDL_AXF_IMPORTER_OPTIONS_H
#define EXAMPLE_AXF_TO_MDL_AXF_IMPORTER_OPTIONS_H

namespace mi { namespace examples { namespace impaxf {

// Command line options structure.
struct Axf_importer_options
{
    // mdl output filename.
    std::string mdl_output_filename;

    std::string axf_module_prefix;
    std::string axf_color_space;
    std::string axf_color_representation;
    
    Axf_importer_options()
        : mdl_output_filename("example_axf_to_mdl.mdl")
        , axf_module_prefix("axf")
        , axf_color_space("sRGB,E")
        , axf_color_representation("all")
    {}
};

}}}
#endif