/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/

// examples/mdl_sdk/dxr/mdl_d3d12/bsdf_measurement.h

#ifndef MDL_D3D12_BSDF_MEASURMENT_H
#define MDL_D3D12_BSDF_MEASURMENT_H

#include "common.h"
#include "example_shared.h"

namespace mi { namespace examples { namespace mdl_d3d12
{
class Base_application;
class Texture;
template <typename T>
class Structured_buffer;

class Bsdf_measurement
{
public:
	struct Part
	{
		Structured_buffer<float>* sample_data = nullptr;
		Structured_buffer<float>* albedo_data = nullptr;
		Texture* evaluation_data = nullptr;
		float max_albedo;
		uint32_t angular_resolution_theta;
		uint32_t angular_resolution_phi;
		uint32_t num_channels;
	};

	Bsdf_measurement(
		Base_application* app,
		const mi::neuraylib::IBsdf_measurement* bsdf_measurement,
		const std::string& debug_name);
	virtual ~Bsdf_measurement();

	bool has_part(mi::neuraylib::Mbsdf_part part) const { return !!m_parts[part].sample_data; }

	const Part& get_part(mi::neuraylib::Mbsdf_part part) const { return m_parts[part]; }

private:
	bool prepare_mbsdf_part(
		Base_application* app,
		mi::neuraylib::Mbsdf_part part,
		const mi::neuraylib::IBsdf_measurement* bsdf_measurement,
		const std::string& debug_name);

	Base_application* m_app;
	std::string m_debug_name;

	Part m_parts[2];
};

}}} // mi::examples::mdl_d3d12
#endif
