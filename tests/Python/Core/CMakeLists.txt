
create_Python_test(PyCore ${CMAKE_CURRENT_LIST_DIR})

file(GLOB entries *.py)
add_custom_target(PyCore_test SOURCES ${entries})
set_target_properties (PyCore_test PROPERTIES
    FOLDER Tests/Python
)
