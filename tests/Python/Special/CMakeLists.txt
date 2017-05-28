
create_Python_test(PySpecial)

file(GLOB entries *.py)
add_custom_target(PySpecial_test SOURCES ${entries})
set_target_properties (PySpecial_test PROPERTIES
    FOLDER Tests/Python
)
