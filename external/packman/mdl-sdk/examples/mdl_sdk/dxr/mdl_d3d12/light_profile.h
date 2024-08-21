/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/

// examples/mdl_sdk/dxr/mdl_d3d12/light_profile.h

#ifndef MDL_D3D12_LIGHT_PROFILE_H
#define MDL_D3D12_LIGHT_PROFILE_H

#include "common.h"
#include "example_shared.h"

namespace mi { namespace examples { namespace mdl_d3d12
{
class Base_application;
class Texture;
template <typename T>
class Structured_buffer;

class Light_profile
{
public:
	Light_profile(
		Base_application* app,
		const mi::neuraylib::ILightprofile* light_profile,
		const std::string& debug_name);
	virtual ~Light_profile();

	Structured_buffer<float>* get_sample_data() const { return m_sample_data; }
	Texture* get_evaluation_data() const { return m_evaluation_data; }
	mi::Uint32_2 get_angular_resolution() const { return m_angular_resolution; }
	mi::Float32_2 get_theta_phi_start() const { return m_theta_phi_start; }
	mi::Float32_2 get_theta_phi_delta() const { return m_theta_phi_delta; }
	float get_candela_multiplier() const { return m_candela_multiplier; }
	float get_total_power() const { return m_total_power; }

private:
	bool create(
		Base_application* app,
		const mi::neuraylib::ILightprofile* light_profile,
		const std::string& debug_name);

	Base_application* m_app;
	std::string m_debug_name;

	Structured_buffer<float>* m_sample_data; // CDF data for sampling
	Texture* m_evaluation_data;
	mi::Uint32_2 m_angular_resolution; // angular resolutio of the grid
	mi::Float32_2 m_theta_phi_start;   // start angles of the grid
	mi::Float32_2 m_theta_phi_delta;   // angular step size
	float m_candela_multiplier;        // factor to rescale the normalized data 
	float m_total_power;
};

}}} // mi::examples::mdl_d3d12
#endif
