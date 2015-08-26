
FILE(GLOB_RECURSE
    ATK_CORE_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_CORE_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKCore_test ${ATK_CORE_TEST_SRC} ${ATK_CORE_TEST_HEADERS})
target_link_libraries (ATKCore_test ATKMock ATKTools ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKCore ATKCore_test --log_level=message)

set_target_properties (ATKCore_test PROPERTIES
    FOLDER Tests
)
