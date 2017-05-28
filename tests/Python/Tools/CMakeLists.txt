
create_Python_test(PyTools)

file(GLOB entries *.py)
add_custom_target(PyTools Scripts SOURCES ${entries})
set_target_properties (PyTools Scripts PROPERTIES
    FOLDER Tests
)
