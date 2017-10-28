
FILE(GLOB
    ATK_TOOLS_SRC
    *.cpp
)

SET(ATK_TOOLS_SIMD_SRC
    SIMD/ApplyGainFilter.cpp
    SIMD/DecimationFilter.cpp
    SIMD/DryWetFilter.cpp
    SIMD/MaxFilter.cpp
    SIMD/MSFilter.cpp
    SIMD/OffsetVolumeFilter.cpp
    SIMD/OneMinusFilter.cpp
    SIMD/SumFilter.cpp
    SIMD/VolumeFilter.cpp
)

FILE(GLOB
    ATK_TOOLS_HEADERS
    *.h*
)

FILE(GLOB
    ATK_TOOLS_SIMD_HEADERS
    SIMD/*.h*
)

SET(ATK_TOOLS_DEFINITIONS)
SET(ATK_TOOLS_INCLUDE)
SET(ATK_TOOLS_LIBRARIES ATKCore)

SET(ATK_TOOLS_NAME ATKTools)
SET(ATK_TOOLS_FOLDER Tools)

ATK_add_library(ATK_TOOLS)
