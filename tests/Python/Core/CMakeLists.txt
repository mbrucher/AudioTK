
create_Python_test(PyCore)

file(GLOB entries *.py)
add_custom_target(PyCoreScripts SOURCES ${entries})
set_target_properties (PyCoreScripts PROPERTIES
    FOLDER Tests
)
