
create_Python_test(PyEQ ${CMAKE_CURRENT_LIST_DIR})

file(GLOB entries *.py)
add_custom_target(PyEQ_test SOURCES ${entries})
set_target_properties (PyEQ_test PROPERTIES
    FOLDER Tests/Python
)
