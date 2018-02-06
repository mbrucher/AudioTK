
create_Python_test(PyDistortion ${CMAKE_CURRENT_LIST_DIR})

file(GLOB entries *.py)
add_custom_target(PyDistortion_test SOURCES ${entries})
set_target_properties (PyDistortion_test PROPERTIES
    FOLDER Tests/Python
)
