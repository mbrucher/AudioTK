
create_Python_test(PyDelay)

file(GLOB entries *.py)
add_custom_target(PyDelayScripts SOURCES ${entries})
set_target_properties (PyDelayScripts PROPERTIES
    FOLDER Tests
)
