
if(ENABLE_PYTHON)
  find_package(PythonInterp REQUIRED)
  add_test(PyAudioTK ${PYTHON_EXECUTABLE} -m nose)
endif(ENABLE_PYTHON)
