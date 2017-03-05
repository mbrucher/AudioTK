
FILE(GLOB_RECURSE
    ATK_ADAPTIVE_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_ADAPTIVE_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${EIGEN_INCLUDE_DIR})

if(EIGEN_FOUND)
add_executable(ATKAdaptive_test ${ATK_ADAPTIVE_TEST_SRC} ${ATK_ADAPTIVE_TEST_HEADERS})
target_link_libraries (ATKAdaptive_test ATKAdaptive ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKAdaptive ATKAdaptive_test --log_level=message)

set_target_properties (ATKAdaptive_test PROPERTIES
    FOLDER Tests
)
endif(EIGEN_FOUND)
