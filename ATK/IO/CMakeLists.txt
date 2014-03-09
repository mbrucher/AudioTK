
FILE(GLOB_RECURSE
    ATK_IO_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_IO_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_library(ATKIO
    SHARED
    ${ATK_IO_SRC} ${ATK_IO_HEADERS}
)
target_link_libraries(ATKIO ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

