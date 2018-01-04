
if((ENABLE_PYTHON STREQUAL "ON") AND (DISABLE_PYTHON_TESTS STREQUAL "OFF"))
  find_package(PythonInterp REQUIRED)

  function(create_Python_test name cwd)
    add_test(NAME ${name} COMMAND ${PYTHON_EXECUTABLE} -m nose --exe WORKING_DIRECTORY ${cwd})
  endfunction(create_Python_test)

  file(GLOB entries *)
  foreach(entry ${entries})
    if(IS_DIRECTORY ${entry} AND EXISTS ${entry}/CMakeLists.txt)
      add_subdirectory(${entry})
    endif()
  endforeach(entry)

endif((ENABLE_PYTHON STREQUAL "ON") AND (DISABLE_PYTHON_TESTS STREQUAL "OFF"))