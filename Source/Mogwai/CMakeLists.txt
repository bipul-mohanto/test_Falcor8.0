add_falcor_executable(Mogwai)
add_definitions(-DXR_USE_GRAPHICS_API_D3D12)

target_sources(Mogwai PRIVATE
    AppData.cpp
    AppData.h
    Mogwai.cpp
    Mogwai.h
    MogwaiScripting.cpp
    MogwaiSettings.cpp
    MogwaiSettings.h

    Extensions/Capture/CaptureTrigger.cpp
    Extensions/Capture/CaptureTrigger.h
    Extensions/Capture/FrameCapture.cpp
    Extensions/Capture/FrameCapture.h
    Extensions/Profiler/TimingCapture.cpp
    Extensions/Profiler/TimingCapture.h

    Extensions/MyVRPlugin/MyVRPlugin.cpp
    Extensions/MyVRPlugin/MyVRPlugin.h

    include/SRanipal.h
    include/SRanipal_Enums.h
    include/SRanipal_Eye.h
    include/SRanipal_Eye_Calibration_Enums.h
    include/SRanipal_EyeData_v1.h
    include/SRanipal_EyeData_v2.h
    include/SRanipal_EyeDataType.h
    include/SRanipal_Lip.h
    include/SRanipal_LipData_v1.h
    include/SRanipal_LipData_v2.h
    include/SRanipal_NotRelease.h
    include/ViveSR_Enums.h
)

target_link_libraries(Mogwai PRIVATE args)

target_source_group(Mogwai "/")


# Add the VR plugin to the build
# add_library(MyVRPlugin SHARED MyVRPlugin.cpp MyVRPlugin.h)
# target_link_libraries(MyVRPlugin PRIVATE Falcor OpenXR)
