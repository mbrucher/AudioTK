
FILE(GLOB_RECURSE
    ATK_DYNAMIC_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_DYNAMIC_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKDynamic_test ${ATK_DYNAMIC_TEST_SRC} ${ATK_DYNAMIC_TEST_HEADERS})
target_link_libraries (ATKDynamic_test ATKDynamic ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKDynamic ATKDynamic_test --log_level=message)

