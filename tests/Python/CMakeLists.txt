
if(ENABLE_PYTHON)
  find_package(PythonInterp REQUIRED)
  if(${PYTHON_VERSION_MAJOR} STREQUAL "2")
    find_program(NOSETESTS3 NAMES nosetests3 HINTS /usr/bin) #for Ubuntu...
    if(${NOSETESTS3})
      add_test(PyAudioTK nosetests3)
    else(${NOSETESTS3})
      add_test(PyAudioTK nosetests)
    endif(${NOSETESTS3})
  else(${PYTHON_VERSION_MAJOR} STREQUAL "2")
    add_test(PyAudioTK nosetests)
  endif(${PYTHON_VERSION_MAJOR} STREQUAL "2")
endif(ENABLE_PYTHON)
