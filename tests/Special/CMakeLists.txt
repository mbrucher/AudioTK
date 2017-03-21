
FILE(GLOB_RECURSE
    ATK_SPECIAL_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_SPECIAL_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKSpecial_test ${ATK_SPECIAL_TEST_SRC} ${ATK_SPECIAL_TEST_HEADERS} ${NATVIS_FILE})
target_link_libraries (ATKSpecial_test ATKSpecial ATKEQ ATKMock ATKTools ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKSpecial ATKSpecial_test --log_level=message)


set_target_properties (ATKSpecial_test PROPERTIES
    FOLDER Tests
)
