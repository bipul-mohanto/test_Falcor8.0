// MyVRPlugin.h
#pragma once

//#include "Mogwai.h" // Include this to define Renderer
#include "../../Mogwai.h"
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#include <openxr/openxr_platform_defines.h>
#include <d3d12.h>
#include "Falcor.h"
#include "Core/SampleApp.h"
#include "Scene/SceneBuilder.h"
#include "RenderGraph/RenderGraph.h"
#include "../../AppData.h"
//#include "AppData.h"

class MyVRPlugin : public Mogwai::Extension
{
public:
    using SharedPtr = std::shared_ptr<MyVRPlugin>;

    // Factory method to create an instance of the plugin
    static SharedPtr create(Mogwai::Renderer* pRenderer) { return SharedPtr(new MyVRPlugin(pRenderer)); }

    // Override methods
    void beginFrame(RenderContext* pRenderContext, const ref<Fbo>& pTargetFbo) override;
    void endFrame(RenderContext* pRenderContext, const ref<Fbo>& pTargetFbo) override;
    void renderUI(Gui* pGui) override;

//private:
// bm: all public 
    // Constructor
    MyVRPlugin(Mogwai::Renderer* pRenderer) : Mogwai::Extension(pRenderer, "MyVRPlugin") {}

    // OpenXR related members
    XrInstance m_instance{XR_NULL_HANDLE};
    XrSession m_session{XR_NULL_HANDLE};
    XrSpace m_appSpace{XR_NULL_HANDLE};
    XrSystemId m_systemId{XR_NULL_SYSTEM_ID}; // Add this line to declare m_systemId

    // Private methods for initialization and rendering
    void initializeOpenXR(RenderContext* pRenderContext); // Pass RenderContext as an argument
    void renderStereo(RenderContext* pRenderContext);
};
