#define XR_USE_GRAPHICS_API_D3D12
#include "OpenXRManager.h"
#include "Utils/Logger.h"
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h> // Ensure this header is included for platform-specific extensions
#include <Core/API/NativeFormats.h>
#include <d3d12.h>

OpenXRManager::OpenXRManager() {}

OpenXRManager::~OpenXRManager()
{
    cleanup();
}

void OpenXRManager::initialize(std::shared_ptr<Falcor::Device> pDevice)
{
    m_pDevice = pDevice;
    createInstance();
    createSession();
    createSwapchains();
}

void OpenXRManager::createInstance()
{
    XrInstanceCreateInfo instanceCreateInfo = {XR_TYPE_INSTANCE_CREATE_INFO};
    instanceCreateInfo.applicationInfo = {"FalcorVRApp", 1, "Falcor", 1, XR_CURRENT_API_VERSION};
    XR_CHECK(xrCreateInstance(&instanceCreateInfo, &m_instance));
}


void OpenXRManager::createSession()
{
    XrSystemGetInfo systemGetInfo = {XR_TYPE_SYSTEM_GET_INFO};
    systemGetInfo.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
    XR_CHECK(xrGetSystem(m_instance, &systemGetInfo, &m_systemId));

    // Initialize the graphics binding for D3D12
    XrGraphicsBindingD3D12KHR graphicsBinding = {};
    graphicsBinding.type = XR_TYPE_GRAPHICS_BINDING_D3D12_KHR;
    graphicsBinding.device = m_pDevice->getNativeHandle().as<ID3D12Device*>();

    // Correctly retrieve the native D3D12 command queue
    //graphicsBinding.queue = static_cast<D3D12CommandQueue*>(m_pDevice->getGfxCommandQueue())->getNativeCommandQueue();

    XrSessionCreateInfo sessionCreateInfo = {XR_TYPE_SESSION_CREATE_INFO};
    sessionCreateInfo.systemId = m_systemId;
    sessionCreateInfo.next = &graphicsBinding;
    XR_CHECK(xrCreateSession(m_instance, &sessionCreateInfo, &m_session));

    XrReferenceSpaceCreateInfo spaceCreateInfo = {XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
    spaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;
    spaceCreateInfo.poseInReferenceSpace.orientation.w = 1.0f;
    XR_CHECK(xrCreateReferenceSpace(m_session, &spaceCreateInfo, &m_appSpace));
}

void OpenXRManager::createSwapchains()
{
    uint32_t viewCount = 0;
    xrEnumerateViewConfigurationViews(m_instance, m_systemId, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0, &viewCount, nullptr);
    m_viewConfigs.resize(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW});
    xrEnumerateViewConfigurationViews(
        m_instance, m_systemId, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, viewCount, &viewCount, m_viewConfigs.data()
    );

    m_swapchains.resize(viewCount); // Ensure swapchains vector is resized

    for (uint32_t i = 0; i < viewCount; ++i)
    {
        XrSwapchainCreateInfo swapchainCreateInfo = {XR_TYPE_SWAPCHAIN_CREATE_INFO};
        swapchainCreateInfo.format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapchainCreateInfo.width = m_viewConfigs[i].recommendedImageRectWidth;
        swapchainCreateInfo.height = m_viewConfigs[i].recommendedImageRectHeight;
        swapchainCreateInfo.sampleCount = m_viewConfigs[i].recommendedSwapchainSampleCount;
        swapchainCreateInfo.arraySize = 1;
        swapchainCreateInfo.mipCount = 1;
        swapchainCreateInfo.faceCount = 1;
        swapchainCreateInfo.usageFlags = XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;

        XR_CHECK(xrCreateSwapchain(m_session, &swapchainCreateInfo, &m_swapchains[i]));
    }
}

void OpenXRManager::render(Falcor::RenderContext* pRenderContext)
{
    XrFrameState frameState = {XR_TYPE_FRAME_STATE};
    XrFrameWaitInfo waitInfo = {XR_TYPE_FRAME_WAIT_INFO};
    XR_CHECK(xrWaitFrame(m_session, &waitInfo, &frameState));

    XrFrameBeginInfo beginInfo = {XR_TYPE_FRAME_BEGIN_INFO};
    XR_CHECK(xrBeginFrame(m_session, &beginInfo));

    for (int eye = 0; eye < 2; ++eye)
    {
        renderEye(pRenderContext, eye);
    }

    XrFrameEndInfo endInfo = {XR_TYPE_FRAME_END_INFO};
    endInfo.displayTime = frameState.predictedDisplayTime;
    XR_CHECK(xrEndFrame(m_session, &endInfo));
}

void OpenXRManager::renderEye(Falcor::RenderContext* pRenderContext, int eye)
{
    // Bind the swapchain image for this eye and render to it
    // Use Falcor's rendering API to render the scene
}

void OpenXRManager::cleanup()
{
    if (m_appSpace != XR_NULL_HANDLE)
    {
        xrDestroySpace(m_appSpace);
        m_appSpace = XR_NULL_HANDLE;
    }
    if (m_session != XR_NULL_HANDLE)
    {
        xrDestroySession(m_session);
        m_session = XR_NULL_HANDLE;
    }
    if (m_instance != XR_NULL_HANDLE)
    {
        xrDestroyInstance(m_instance);
        m_instance = XR_NULL_HANDLE;
    }
}
