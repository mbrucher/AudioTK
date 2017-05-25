
FIND_PACKAGE(SWIG REQUIRED)
FIND_PACKAGE(PythonLibs REQUIRED)
FIND_PACKAGE(Numpy REQUIRED)

add_subdirectory(pybind11)

INCLUDE(${SWIG_USE_FILE})
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH} ${PYTHON_NUMPY_INCLUDE_DIR})

SET(CMAKE_SWIG_FLAGS "")

string(REGEX REPLACE ".*/(python[0-9]\\.[0-9])" "\\1" PYTHON_FOLDER ${PYTHON_INCLUDE_DIR})

file(GLOB entries *)
foreach(entry ${entries})
  if(IS_DIRECTORY ${entry} AND EXISTS ${entry}/CMakeLists.txt)
    add_subdirectory(${entry})
  endif()
endforeach(entry)

INSTALL(FILES __init__.py DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK)

