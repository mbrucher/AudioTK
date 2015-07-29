
INSTALL(FILES ${PROJECT_BINARY_DIR}/ATK/config.h ${PROJECT_BINARY_DIR}/ATK/git.h
   DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ATK
    )

add_subdirectory(Core)

if(ENABLE_TESTS)
  add_subdirectory(Mock)
endif(ENABLE_TESTS)

add_subdirectory(Tools)

add_subdirectory(IO)

add_subdirectory(EQ)
add_subdirectory(Delay)
add_subdirectory(Dynamic)
add_subdirectory(Distortion)

add_subdirectory(Special)
