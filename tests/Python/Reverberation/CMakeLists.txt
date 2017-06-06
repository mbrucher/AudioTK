
create_Python_test(PyReverberation ${CMAKE_CURRENT_LIST_DIR})

file(GLOB entries *.py)
add_custom_target(PyReverberation_test SOURCES ${entries})
set_target_properties (PyReverberation_test PROPERTIES
    FOLDER Tests/Python
)
