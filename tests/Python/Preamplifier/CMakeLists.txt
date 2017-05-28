
create_Python_test(PyPreamplifier)

file(GLOB entries *.py)
add_custom_target(PyPreamplifier_test SOURCES ${entries})
set_target_properties (PyPreamplifier_test PROPERTIES
    FOLDER Tests/Python
)
