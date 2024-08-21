#*****************************************************************************
# Copyright 2023 NVIDIA Corporation. All rights reserved.
#*****************************************************************************

set(PROJECT_NAME examples-mdl_python-tests)

# create target from template
create_from_python_preset(
    TARGET ${PROJECT_NAME}
    MAIN "__init__.py"
    SOURCES
        "__init__.py"
        "setup.py"
        "test_mi_idata.py"
    )
