#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

# -------------------------------------------------------------------------------------------------
# script expects the following variables:
    # - TARGET_ADD_TOOL_DEPENDENCY_TARGET
    # - TARGET_ADD_TOOL_DEPENDENCY_TOOL
# -------------------------------------------------------------------------------------------------

# first we need to build mdltlc, so we add the dependency manually
add_dependencies(${TARGET_ADD_TOOL_DEPENDENCY_TARGET} prod-bin-mdltlc)

# set the path
# note, that this is an generator expression, that will be evaluated by the build system (not during configuration)
set(mdltlc_PATH "$<TARGET_FILE:prod-bin-mdltlc>" CACHE INTERNAL "")
