
create_Python_test(PyPreamplifier)

file(GLOB entries *.py)
add_custom_target(PyPreamplifierScripts SOURCES ${entries})
set_target_properties (PyPreamplifierScripts PROPERTIES
    FOLDER Tests
)
