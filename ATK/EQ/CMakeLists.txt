
FILE(GLOB
    ATK_EQ_SRC
    *.cpp
)

SET(
  ATK_EQ_SIMD_SRC
  SIMD/BesselFilter.cpp
  SIMD/ButterworthFilter.cpp
  SIMD/Chebyshev1Filter.cpp
  SIMD/Chebyshev2Filter.cpp
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

SET(ATK_EQ_DEFINITIONS)
SET(ATK_EQ_INCLUDE)
SET(ATK_EQ_LIBRARIES ATKCore ATKUtility)

IF(EIGEN_FOUND)
  LIST(APPEND ATK_EQ_INCLUDE ${EIGEN_INCLUDE_DIRS})
ENDIF(EIGEN_FOUND)

SET(ATK_EQ_NAME ATKEQ)
SET(ATK_EQ_FOLDER EQ)

ATK_add_library(ATK_EQ)
