
FILE(GLOB_RECURSE
    ATK_TOOLS_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_TOOLS_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKTools_test ${ATK_TOOLS_TEST_SRC} ${ATK_TOOLS_TEST_HEADERS})
target_link_libraries (ATKTools_test ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKTools ATKTools_test --log_level=message)

