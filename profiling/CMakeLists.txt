add_subdirectory(Delay)
add_subdirectory(Dynamic)
add_subdirectory(EQ)

if(EIGEN_FOUND)
add_subdirectory(Preamplifier)
endif(EIGEN_FOUND)
