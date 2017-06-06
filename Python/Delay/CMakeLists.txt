
FILE(GLOB_RECURSE
  PYTHON_MODULE_Delay_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Delay_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonDelay MODULE ${PYTHON_MODULE_Delay_SRC} ${PYTHON_MODULE_Delay_HEADERS})
target_link_libraries(PythonDelay PRIVATE ATKCore ATKDelay)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Delay
    )
INSTALL(TARGETS PythonDelay
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Delay
    )

set_target_properties (PythonDelay PROPERTIES
    FOLDER Python
)
