
create_Python_test(PySpecial)

file(GLOB entries *.py)
add_custom_target(PySpecialScripts SOURCES ${entries})
set_target_properties (PySpecialScripts PROPERTIES
    FOLDER Tests
)
