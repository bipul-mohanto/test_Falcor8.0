#pragma once
#include <openxr/openxr.h>
#include "Falcor.h"

//class OpenXRManager
//{
//public:
//    void initialize(Falcor::Device::SharedPtr pDevice);
//    void render(Falcor::RenderContext* pRenderContext);
//    void cleanup();
//
//private:
//    void createInstance();
//    void createSession();
//    void createSwapchains();
//    void pollEvents();
//
//    XrInstance m_instance = XR_NULL_HANDLE;
//    XrSession m_session = XR_NULL_HANDLE;
//    XrSystemId m_systemId = XR_NULL_SYSTEM_ID;
//    std::vector<XrSwapchain> m_swapchains;
//    Falcor::Device::SharedPtr m_pDevice;
//};
