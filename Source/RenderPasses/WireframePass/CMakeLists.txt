add_plugin(WireframePass)

target_sources(WireframePass PRIVATE
    WireframePass.cpp
    WireframePass.h
    WireframePass.3d.slang
)

target_source_group(WireframePass "RenderPasses")
