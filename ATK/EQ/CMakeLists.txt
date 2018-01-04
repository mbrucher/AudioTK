
FILE(GLOB
    ATK_EQ_SRC
    *.cpp
)

SET(
  ATK_EQSIMD_SIMD_SRC
  SIMD/BesselFilter.cpp
  SIMD/ButterworthFilter.cpp
  SIMD/Chebyshev1Filter.cpp
  SIMD/Chebyshev2Filter.cpp
)

SET(
  ATK_EQSIMD2_SIMD_SRC
  SIMD/FourthOrderFilter.cpp
  SIMD/LinkwitzRileyFilter.cpp
  SIMD/RIAAFilter.cpp
  SIMD/RobertBristowJohnsonFilter.cpp
  SIMD/SecondOrderFilter.cpp
)

FILE(GLOB
    ATK_EQ_HEADERS
    *.h*
)

FILE(GLOB
    ATK_EQSIMD_SIMD_HEADERS
  SIMD/BesselFilter.h
  SIMD/ButterworthFilter.h
  SIMD/Chebyshev1Filter.h
  SIMD/Chebyshev2Filter.h
)

FILE(GLOB
    ATK_EQSIMD2_SIMD_HEADERS
  SIMD/FourthOrderFilter.h
  SIMD/LinkwitzRileyFilter.h
  SIMD/RIAAFilter.h
  SIMD/RobertBristowJohnsonFilter.h
  SIMD/SecondOrderFilter.h
)

SET(ATK_EQ_DEFINITIONS)
SET(ATK_EQ_INCLUDE)
SET(ATK_EQ_LIBRARIES ATKCore ATKUtility)
SET(ATK_EQSIMD_LIBRARIES ATKEQ ATKCore ATKUtility)
SET(ATK_EQSIMD2_LIBRARIES ATKEQ ATKCore ATKUtility)

LIST(APPEND ATK_EQ_INCLUDE ${EIGEN3_INCLUDE_DIR})

SET(ATK_EQ_NAME ATKEQ)
SET(ATK_EQSIMD_NAME ATKEQSIMD)
SET(ATK_EQSIMD2_NAME ATKEQSIMD2)
SET(ATK_EQ_FOLDER EQ)
SET(ATK_EQSIMD_FOLDER EQ/SIMD)
SET(ATK_EQSIMD2_FOLDER EQ/SIMD)

ATK_add_library(ATK_EQ)
if(ENABLE_SIMD)
  ATK_add_library(ATK_EQSIMD)
  ATK_add_library(ATK_EQSIMD2)
endif(ENABLE_SIMD)
