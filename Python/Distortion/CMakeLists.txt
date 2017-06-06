
FILE(GLOB_RECURSE
  PYTHON_MODULE_Distortion_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Distortion_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonDistortion MODULE ${PYTHON_MODULE_Distortion_SRC} ${PYTHON_MODULE_Distortion_HEADERS})
target_link_libraries(PythonDistortion PRIVATE ATKCore ATKDistortion)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Distortion
    )
INSTALL(TARGETS PythonDistortion
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Distortion
    )

set_target_properties (PythonDistortion PROPERTIES
    FOLDER Python
)
