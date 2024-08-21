#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

set(PROJECT_NAME examples-mdl_python-pymdl_inspection)

# create target from template
create_from_python_preset(
    TARGET ${PROJECT_NAME}
    MAIN "example_pymdl_inspection.py"
    SOURCES
        "example_pymdl_inspection.py"
    )
