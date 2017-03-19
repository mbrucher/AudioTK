
FILE(GLOB_RECURSE
    ATK_PREAMPLIFIER_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_PREAMPLIFIER_TEST_HEADERS
    *.h
)

if(EIGEN_FOUND)
include_directories(${PROJECT_SOURCE_DIR} ${EIGEN_INCLUDE_DIR})

add_executable(ATKPreamplifier_test ${ATK_PREAMPLIFIER_TEST_SRC} ${ATK_PREAMPLIFIER_TEST_HEADERS})
target_link_libraries (ATKPreamplifier_test ATKPreamplifier ATKEQ ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKPreamplifier ATKPreamplifier_test --log_level=message)

set_target_properties (ATKPreamplifier_test PROPERTIES
    FOLDER Tests
)
endif(EIGEN_FOUND)
