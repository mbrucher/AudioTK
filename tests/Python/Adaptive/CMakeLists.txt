
create_Python_test(PyAdaptive)

file(GLOB entries *.py)
add_custom_target(PyAdaptiveScripts SOURCES ${entries})
set_target_properties (PyAdaptiveScripts PROPERTIES
    FOLDER Tests
)
