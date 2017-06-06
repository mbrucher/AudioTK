
FILE(GLOB_RECURSE
  PYTHON_MODULE_Reverberation_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_Reverberation_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS})

pybind11_add_module(PythonReverberation MODULE ${PYTHON_MODULE_Reverberation_SRC} ${PYTHON_MODULE_Reverberation_HEADERS})
target_link_libraries(PythonReverberation PRIVATE ATKCore ATKReverberation)


INSTALL(FILES __init__.py
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Reverberation
    )
INSTALL(TARGETS PythonReverberation
    DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/Reverberation
    )

set_target_properties (PythonReverberation PROPERTIES
    FOLDER Python
)
