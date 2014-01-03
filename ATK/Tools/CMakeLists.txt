
FILE(GLOB_RECURSE
    ATK_TOOLS_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_TOOLS_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_library(ATKTools
    SHARED
    ${ATK_TOOLS_SRC} ${ATK_TOOLS_HEADERS}
)

