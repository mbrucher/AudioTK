
FILE(GLOB_RECURSE
  PYTHON_MODULE_Core_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Core_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonCore MODULE ${PYTHON_MODULE_Core_SRC} ${PYTHON_MODULE_Core_HEADERS})
target_link_libraries(PythonCore PRIVATE ATKCore)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Core
    )
INSTALL(TARGETS PythonCore
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Core
    )

set_target_properties (PythonCore PROPERTIES
    FOLDER Python
)
