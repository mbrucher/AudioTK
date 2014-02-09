
FILE(GLOB_RECURSE
    ATK_EQ_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_EQ_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_library(ATKEQ
    SHARED
    ${ATK_EQ_SRC} ${ATK_EQ_HEADERS}
)
target_link_libraries(ATKEQ ATKCore)

