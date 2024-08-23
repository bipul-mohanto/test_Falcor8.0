add_falcor_executable(MogwaiVR)

target_sources(MogwaiVR PRIVATE
    AppData.cpp
    AppData.h
    Mogwai.cpp
    Mogwai.h
    MogwaiScripting.cpp
    MogwaiSettings.cpp
    MogwaiSettings.h

    OpenXRManager.h
    OpenXRManager.cpp

    Extensions/Capture/CaptureTrigger.cpp
    Extensions/Capture/CaptureTrigger.h
    Extensions/Capture/FrameCapture.cpp
    Extensions/Capture/FrameCapture.h
    Extensions/Profiler/TimingCapture.cpp
    Extensions/Profiler/TimingCapture.h

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

target_link_libraries(MogwaiVR PRIVATE args)

target_source_group(MogwaiVR "/")
