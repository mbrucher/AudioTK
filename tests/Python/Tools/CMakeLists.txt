
create_Python_test(PyTools ${CMAKE_CURRENT_LIST_DIR})

file(GLOB entries *.py)
add_custom_target(PyTools_test SOURCES ${entries})
set_target_properties (PyTools_test PROPERTIES
    FOLDER Tests/Python
)
