
create_Python_test(PyPreamplifier ${CMAKE_CURRENT_LIST_DIR})

file(GLOB entries *.py)
add_custom_target(PyPreamplifier_test SOURCES ${entries})
set_target_properties (PyPreamplifier_test PROPERTIES
    FOLDER Tests/Python
)
