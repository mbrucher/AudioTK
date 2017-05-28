
FILE(GLOB_RECURSE
  PYTHON_MODULE_Tools_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Tools_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonTools MODULE ${PYTHON_MODULE_Tools_SRC} ${PYTHON_MODULE_Tools_HEADERS})
target_link_libraries(PythonTools PRIVATE ATKCore ATKTools)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Tools
    )
INSTALL(TARGETS PythonTools
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Tools
    )

set_target_properties (PythonTools PROPERTIES
    FOLDER Python
)
