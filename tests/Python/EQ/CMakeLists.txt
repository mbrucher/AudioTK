
create_Python_test(PyEQ)

file(GLOB entries *.py)
add_custom_target(PyEQ_test SOURCES ${entries})
set_target_properties (PyEQ_test PROPERTIES
    FOLDER Tests/Python
)
