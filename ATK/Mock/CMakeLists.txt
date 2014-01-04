
FILE(GLOB_RECURSE
    ATK_MOCK_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_MOCK_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_library(ATKMock
    SHARED
    ${ATK_MOCK_SRC} ${ATK_MOCK_HEADERS}
)
target_link_libraries(ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

