/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/

// examples/mdl_sdk/dxr/mdl_d3d12/gltf.h

#ifndef MDL_D3D12_GLTF_H
#define MDL_D3D12_GLTF_H

#include "common.h"
#include "scene.h"

namespace mi { namespace examples { namespace mdl_d3d12
{
    class Loader_gltf : public IScene_loader
    {
    public:
        virtual ~Loader_gltf() = default;

        bool load(Mdl_sdk& sdk, const std::string& file_name, const Scene_options& options) override;
        std::unique_ptr<const IScene_loader::Scene> move_scene() override
        {
            return std::move(m_scene);
        }

        // replace all materials in the scene by one specified on the command line
        void replace_all_materials(const std::string& material_name);

    private:
        std::unique_ptr<IScene_loader::Scene> m_scene;
    };

}}} // mi::examples::mdl_d3d12
#endif
