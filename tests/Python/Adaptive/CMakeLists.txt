
create_Python_test(PyAdaptive)

file(GLOB entries *.py)
add_custom_target(PyAdaptive_test SOURCES ${entries})
set_target_properties (PyAdaptive_test PROPERTIES
    FOLDER Tests/Python
)
