
create_Python_test(PyDynamic)

file(GLOB entries *.py)
add_custom_target(PyDynamic_test SOURCES ${entries})
set_target_properties (PyDynamic_test PROPERTIES
    FOLDER Tests/Python
)
