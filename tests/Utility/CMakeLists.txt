
FILE(GLOB_RECURSE
    ATK_UTILITY_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_UTILITY_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKUtility_test ${ATK_UTILITY_TEST_SRC} ${ATK_UTILITY_TEST_HEADERS} ${NATVIS_FILE})
target_link_libraries (ATKUtility_test ATKUtility ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKUtility ATKUtility_test --log_level=message)

set_target_properties (ATKUtility_test PROPERTIES
    FOLDER Tests
)
