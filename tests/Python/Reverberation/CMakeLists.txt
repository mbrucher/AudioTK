
create_Python_test(PyReverberation)

file(GLOB entries *.py)
add_custom_target(PyReverberationScripts SOURCES ${entries})
set_target_properties (PyReverberationScripts PROPERTIES
    FOLDER Tests
)
