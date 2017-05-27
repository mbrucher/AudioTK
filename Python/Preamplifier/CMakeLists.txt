
FILE(GLOB_RECURSE
  PYTHON_MODULE_Preamplifier_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Preamplifier_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonPreamplifier MODULE ${PYTHON_MODULE_Preamplifier_SRC} ${PYTHON_MODULE_Preamplifier_HEADERS})
target_link_libraries(PythonPreamplifier PRIVATE ATKCore ATKPreamplifier)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Preamplifier
    )
INSTALL(TARGETS PythonPreamplifier
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Preamplifier
    )

set_target_properties (PythonPreamplifier PROPERTIES
    FOLDER Python
)
