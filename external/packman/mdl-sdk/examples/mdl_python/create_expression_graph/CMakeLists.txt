#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

set(PROJECT_NAME examples-mdl_python-create_expression_graph)

# create target from template
create_from_python_preset(
    TARGET ${PROJECT_NAME}
    MAIN "example_create_expression_graph.py"
    SOURCES
        "example_create_expression_graph.py"
    )
