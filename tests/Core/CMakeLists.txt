
FILE(GLOB_RECURSE
    ATK_CORE_TEST_SRC
    *.cpp
    Mock/*.cpp
)

FILE(GLOB_RECURSE
    ATK_CORE_TEST_HEADERS
    *.h
    Mock/*.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKCore_test ${ATK_CORE_TEST_SRC} ${ATK_CORE_TEST_HEADERS})
target_link_libraries (ATKCore_test ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKCore ATKCore_test --log_level=message)
