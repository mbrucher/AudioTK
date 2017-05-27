
FILE(GLOB_RECURSE
  PYTHON_MODULE_Adaptive_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Adaptive_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonAdaptive MODULE ${PYTHON_MODULE_Adaptive_SRC} ${PYTHON_MODULE_Adaptive_HEADERS})
target_link_libraries(PythonAdaptive PRIVATE ATKCore ATKAdaptive)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Adaptive
    )
INSTALL(TARGETS PythonAdaptive
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Adaptive
    )

set_target_properties (PythonAdaptive PROPERTIES
    FOLDER Python
)
