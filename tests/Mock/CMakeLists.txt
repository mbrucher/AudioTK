
FILE(GLOB_RECURSE
    ATK_MOCK_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_MOCK_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKMock_test ${ATK_MOCK_TEST_SRC} ${ATK_MOCK_TEST_HEADERS})
target_link_libraries (ATKMock_test ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKMock ATKMock_test --log_level=message)

