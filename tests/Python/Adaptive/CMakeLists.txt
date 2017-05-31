
create_Python_test(PyAdaptive ${CMAKE_CURRENT_LIST_DIR})

file(GLOB entries *.py)
add_custom_target(PyAdaptive_test SOURCES ${entries})
set_target_properties (PyAdaptive_test PROPERTIES
    FOLDER Tests/Python
)
