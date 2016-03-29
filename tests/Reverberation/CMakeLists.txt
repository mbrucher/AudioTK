
FILE(GLOB_RECURSE
    ATK_REVERBERATION_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_REVERBERATION_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKReverberation_test ${ATK_REVERBERATION_TEST_SRC} ${ATK_REVERBERATION_TEST_HEADERS})
target_link_libraries (ATKReverberation_test ATKReverberation ATKMock ATKTools ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKReverberation ATKReverberation_test --log_level=message)


set_target_properties (ATKReverberation_test PROPERTIES
    FOLDER Tests
)
