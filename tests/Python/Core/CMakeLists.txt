
create_Python_test(PyCore)

file(GLOB entries *.py)
add_custom_target(PyCore_test SOURCES ${entries})
set_target_properties (PyCore_test PROPERTIES
    FOLDER Tests/Python
)
