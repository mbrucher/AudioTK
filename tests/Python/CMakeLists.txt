
if(ENABLE_PYTHON)
  add_test(PyAudioTK ${PYTHON_EXECUTABLE} -m nose)
endif(ENABLE_PYTHON)
