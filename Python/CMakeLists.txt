
FIND_PACKAGE(Numpy REQUIRED)

file(GLOB entries *)
foreach(entry ${entries})
  if(IS_DIRECTORY ${entry} AND EXISTS ${entry}/CMakeLists.txt)
    add_subdirectory(${entry})
  endif()
endforeach(entry)

INSTALL(FILES __init__.py DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK)

