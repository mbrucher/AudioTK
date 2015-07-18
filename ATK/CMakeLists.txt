
INSTALL(FILES ${PROJECT_BINARY_DIR}/ATK/config.h ${PROJECT_BINARY_DIR}/ATK/git.h
   DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ATK
    )

add_subdirectory(Core)

add_subdirectory(Mock)
add_subdirectory(Tools)

add_subdirectory(IO)

add_subdirectory(EQ)
add_subdirectory(Delay)
add_subdirectory(Dynamic)
add_subdirectory(Distortion)

if(EIGEN_FOUND)
add_subdirectory(Adaptive)
endif(EIGEN_FOUND)
