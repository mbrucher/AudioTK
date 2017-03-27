
FILE(GLOB_RECURSE
    ATK_DELAY_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_DELAY_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKDelay_test ${ATK_DELAY_TEST_SRC} ${ATK_DELAY_TEST_HEADERS} ${NATVIS_FILE})
target_link_libraries (ATKDelay_test ATKDelay ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKDelay ATKDelay_test --log_level=message)

set_target_properties (ATKDelay_test PROPERTIES
    FOLDER Tests
)
