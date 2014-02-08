
FILE(GLOB_RECURSE
    ATK_EQ_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_EQ_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKEQ_test ${ATK_EQ_TEST_SRC} ${ATK_EQ_TEST_HEADERS})
target_link_libraries (ATKEQ_test ATKEQ ATKToolsATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKEQ ATKEQ_test --log_level=message)

