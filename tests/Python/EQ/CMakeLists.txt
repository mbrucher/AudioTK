
create_Python_test(PyEQ)

file(GLOB entries *.py)
add_custom_target(PyEQScripts SOURCES ${entries})
set_target_properties (PyEQScripts PROPERTIES
    FOLDER Tests
)
