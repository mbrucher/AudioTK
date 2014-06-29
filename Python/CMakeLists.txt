
FIND_PACKAGE(SWIG REQUIRED)
FIND_PACKAGE(PythonLibs REQUIRED)
FIND_PACKAGE(Numpy REQUIRED)

INCLUDE(${SWIG_USE_FILE})
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

SET(CMAKE_SWIG_FLAGS "")

string(REGEX REPLACE ".*/(python[0-9]\\.[0-9])" "\\1" PYTHON_FOLDER ${PYTHON_INCLUDE_DIR})

add_subdirectory(Core)
add_subdirectory(Tools)
add_subdirectory(EQ)
add_subdirectory(Delay)
add_subdirectory(Dynamic)
add_subdirectory(Distortion)

INSTALL(FILES __init__.py DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK)

