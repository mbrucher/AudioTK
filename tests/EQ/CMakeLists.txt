
FILE(GLOB_RECURSE
    ATK_EQ_TEST_SRC
main.cpp
Bessel.cpp
Butterworth.cpp
ChamberlinFilter.cpp
Chebyshev1Filter.cpp
Chebyshev2Filter.cpp
LinkwitzRileyFilter.cpp
RobertBristowJohnsonFilter.cpp
SD1ToneFilter.cpp
SecondOrderFilter.cpp
SecondOrderSVFFilter.cpp
TimeVaryingSecondOrderFilter.cpp
ToneStackFilter.cpp
)

FILE(GLOB_RECURSE
    ATK_EQ_TEST_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKEQ_test ${ATK_EQ_TEST_SRC} ${ATK_EQ_TEST_HEADERS})
target_link_libraries (ATKEQ_test ATKEQ ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKEQ ATKEQ_test --log_level=message)

set_target_properties (ATKEQ_test PROPERTIES
    FOLDER Tests
)
