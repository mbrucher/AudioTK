
FILE(GLOB_RECURSE
  PYTHON_MODULE_Special_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Special_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonSpecial MODULE ${PYTHON_MODULE_Special_SRC} ${PYTHON_MODULE_Special_HEADERS})
target_link_libraries(PythonSpecial PRIVATE ATKCore ATKSpecial)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Special
    )
INSTALL(TARGETS PythonSpecial
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Special
    )

set_target_properties (PythonSpecial PROPERTIES
    FOLDER Python
)
