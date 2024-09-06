#pragma once

// Ensure that XR_USE_GRAPHICS_API_D3D12 is defined before including the headers if needed
#ifndef XR_USE_GRAPHICS_API_D3D12
#define XR_USE_GRAPHICS_API_D3D12
#endif


// MyVRPlugin.cpp
//"C:\Users\local-admin\Desktop\Falcor\Source\Mogwai\MyVRPlugin.h"
#include "C:/Users/local-admin/Desktop/Falcor/Source/Mogwai/Extensions/MyVRPlugin/MyVRPlugin.h"
#include "C:/Users/local-admin/Desktop/Falcor/Source/Falcor/Core/API/RenderContext.h"
//#include "Falcor/Core/API/RenderContext.h" // Include necessary Falcor components

// Ensure OpenXR headers are included after the macro definition
#include <openxr/openxr_platform.h>
#include <stdexcept>
#include <iostream>

#include <d3d12.h>



void MyVRPlugin::beginFrame(RenderContext* pRenderContext, const ref<Fbo>& pTargetFbo)
{
    // Implementation here
}

void MyVRPlugin::endFrame(RenderContext* pRenderContext, const ref<Fbo>& pTargetFbo)
{
    // Implementation here
}

void MyVRPlugin::initializeOpenXR(RenderContext* pRenderContext)
{
    XrSystemGetInfo systemGetInfo = {XR_TYPE_SYSTEM_GET_INFO};
    systemGetInfo.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;

    if (xrGetSystem(m_instance, &systemGetInfo, &m_systemId) != XR_SUCCESS)
    {
        throw std::runtime_error("Failed to get OpenXR system");
    }

    XrGraphicsBindingD3D12KHR graphicsBinding = {};
    graphicsBinding.type = XR_TYPE_GRAPHICS_BINDING_D3D12_KHR;
    graphicsBinding.device = static_cast<ID3D12Device*>(pRenderContext->getDevice()->getNativeHandle().as<ID3D12Device>());
    graphicsBinding.queue =
        static_cast<ID3D12CommandQueue*>(pRenderContext->getDevice()->getGfxCommandQueue()->getNativeHandleAs<ID3D12CommandQueue>());

    XrSessionCreateInfo sessionCreateInfo = {XR_TYPE_SESSION_CREATE_INFO};
    sessionCreateInfo.systemId = m_systemId;
    sessionCreateInfo.next = &graphicsBinding;

    if (xrCreateSession(m_instance, &sessionCreateInfo, &m_session) != XR_SUCCESS)
    {
        throw std::runtime_error("Failed to create OpenXR session");
    }

    XrReferenceSpaceCreateInfo spaceCreateInfo = {XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
    spaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;
    spaceCreateInfo.poseInReferenceSpace.orientation.w = 1.0f;

    if (xrCreateReferenceSpace(m_session, &spaceCreateInfo, &m_appSpace) != XR_SUCCESS)
    {
        throw std::runtime_error("Failed to create OpenXR reference space");
    }
}
void MyVRPlugin::renderStereo(RenderContext* pRenderContext)
{
    // Stereoscopic rendering implementation
}

void MyVRPlugin::renderUI(Gui* pGui)
{
//    auto widgets = pGui->Widgets();                  // Assuming there is a method to get a Widgets instance
//    widgets.text("VR Plugin Settings", false);       // Displays a label/text
//    widgets.checkbox("Enable VR", m_vrEnabled, false); // Checkbox for enabling/disabling VR
//
}


// Register the plugin
#include <memory>

// Forward declaration of Mogwai::Extension
namespace Mogwai {
    class Extension;
}

// Modify the signature of getExtensions function
extern "C" __declspec(dllexport) void getExtensions(std::vector<std::shared_ptr<Mogwai::Extension>>& extensions)
{
    // Implementation here
    extensions.push_back(MyVRPlugin::create(nullptr)); // Pass the required argument to the create() function
}
