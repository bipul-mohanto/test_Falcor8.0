#include "OpenXRManager.h"
#include "Utils/Logger.h"

//void OpenXRManager::initialize(Falcor::Device::SharedPtr pDevice)
//{
//    m_pDevice = pDevice;
//    createInstance();
//    createSession();
//    createSwapchains();
//}
//
//void OpenXRManager::createInstance()
//{
//    XrInstanceCreateInfo createInfo{XR_TYPE_INSTANCE_CREATE_INFO};
//    createInfo.applicationInfo = {"Mogwai", 1, "Falcor", 1, XR_CURRENT_API_VERSION};
//    XR_CHECK(xrCreateInstance(&createInfo, &m_instance));
//}
//
//void OpenXRManager::createSession()
//{
//    XrSystemGetInfo systemInfo{XR_TYPE_SYSTEM_GET_INFO};
//    systemInfo.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
//    XR_CHECK(xrGetSystem(m_instance, &systemInfo, &m_systemId));
//
//    XrGraphicsBindingD3D12KHR d3d12Binding{XR_TYPE_GRAPHICS_BINDING_D3D12_KHR};
//    d3d12Binding.device = m_pDevice->getNativeHandle();
//
//    XrSessionCreateInfo sessionInfo{XR_TYPE_SESSION_CREATE_INFO};
//    sessionInfo.systemId = m_systemId;
//    sessionInfo.next = &d3d12Binding;
//
//    XR_CHECK(xrCreateSession(m_instance, &sessionInfo, &m_session));
//}
//
//void OpenXRManager::createSwapchains()
//{
//    // Detailed swapchain creation based on the system's capabilities
//}
//
//void OpenXRManager::render(Falcor::RenderContext* pRenderContext)
//{
//    // Poll events, prepare frame, render each eye, and submit
//}
//
//void OpenXRManager::cleanup()
//{
//    xrDestroySession(m_session);
//    xrDestroyInstance(m_instance);
//}
