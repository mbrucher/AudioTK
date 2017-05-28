
FIND_PACKAGE(Numpy REQUIRED)

add_subdirectory(pybind11)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Python/pybind11/tools ${CMAKE_MODULE_PATH})
FIND_PACKAGE(PythonLibsNew REQUIRED)

file(GLOB entries *)
foreach(entry ${entries})
  if(IS_DIRECTORY ${entry} AND EXISTS ${entry}/CMakeLists.txt AND NOT ${entry} STREQUAL "${CMAKE_SOURCE_DIR}/Python/pybind11")
    add_subdirectory(${entry})
  endif()
endforeach(entry)

INSTALL(FILES __init__.py DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK)

