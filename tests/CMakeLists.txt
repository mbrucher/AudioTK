add_subdirectory(Utility)
add_subdirectory(Core)
add_subdirectory(Mock)
add_subdirectory(Tools)

add_subdirectory(IO)

add_subdirectory(EQ)
add_subdirectory(Delay)
add_subdirectory(Dynamic)
add_subdirectory(Distortion)

add_subdirectory(Special)

if(ENABLE_PYTHON)
  add_subdirectory(Python)
endif(ENABLE_PYTHON)
