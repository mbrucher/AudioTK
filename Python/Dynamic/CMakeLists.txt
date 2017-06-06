
FILE(GLOB_RECURSE
  PYTHON_MODULE_Dynamic_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Dynamic_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonDynamic MODULE ${PYTHON_MODULE_Dynamic_SRC} ${PYTHON_MODULE_Dynamic_HEADERS})
target_link_libraries(PythonDynamic PRIVATE ATKCore ATKDynamic)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Dynamic
    )
INSTALL(TARGETS PythonDynamic
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Dynamic
    )

set_target_properties (PythonDynamic PROPERTIES
    FOLDER Python
)
