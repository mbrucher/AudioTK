INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})


SET(CMAKE_SWIG_FLAGS "")

string(REGEX REPLACE ".*/(python[0-9]\\.[0-9])" "\\1" PYTHON_FOLDER ${PYTHON_INCLUDE_DIR})

add_subdirectory(Core)
add_subdirectory(Tools)
add_subdirectory(EQ)

INSTALL(FILES __init__.py DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${PYTHON_FOLDER}/site-packages/ATK)

