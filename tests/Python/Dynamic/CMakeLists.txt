
create_Python_test(PyDynamic)

file(GLOB entries *.py)
add_custom_target(PyDynamicScripts SOURCES ${entries})
set_target_properties (PyDynamicScripts PROPERTIES
    FOLDER Tests
)
