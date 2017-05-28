
create_Python_test(PyDelay)

file(GLOB entries *.py)
add_custom_target(PyDelay_test SOURCES ${entries})
set_target_properties (PyDelay_test PROPERTIES
    FOLDER Tests/Python
)
