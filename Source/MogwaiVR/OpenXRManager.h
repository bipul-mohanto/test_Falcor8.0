#ifndef OPENXR_MANAGER_H
#define OPENXR_MANAGER_H

#define XR_USE_GRAPHICS_API_D3D12
#include <stdexcept>
#include <string>
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#include <Core/API/ShaderTable.h>
#include <memory>
#include <vector>

// Define the XR_CHECK macro
#define XR_CHECK(result)                                                                                     \
    do                                                                                                       \
    {                                                                                                        \
        XrResult xrResult = (result);                                                                        \
        if (xrResult != XR_SUCCESS)                                                                          \
        {                                                                                                    \
            throw std::runtime_error("OpenXR API call failed with error code: " + std::to_string(xrResult)); \
        }                                                                                                    \
    } while (false)

// Other includes and declarations...

class OpenXRManager
{
public:
    OpenXRManager();
    ~OpenXRManager();
    void initialize(std::shared_ptr<Falcor::Device> pDevice);
    void render(Falcor::RenderContext* pRenderContext);
    void cleanup();

private:
    void createInstance();
    void createSession();
    void createSwapchains();
    void renderEye(Falcor::RenderContext* pRenderContext, int eye);

    XrInstance m_instance = XR_NULL_HANDLE;
    XrSession m_session = XR_NULL_HANDLE;
    XrSystemId m_systemId = XR_NULL_SYSTEM_ID;
    XrSpace m_appSpace = XR_NULL_HANDLE; // Declare m_appSpace here
    std::shared_ptr<Falcor::Device> m_pDevice;
    std::vector<XrViewConfigurationView> m_viewConfigs;
    std::vector<XrSwapchain> m_swapchains;
};

#endif // OPENXR_MANAGER_H
