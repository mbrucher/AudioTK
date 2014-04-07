
FILE(GLOB_RECURSE
    ATK_DISTORTION_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_DISTORTION_TEST_HEADERS
    *.h
)

if(LIBSNDFILE_FOUND)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKDistortion_test ${ATK_DISTORTION_TEST_SRC} ${ATK_DISTORTION_TEST_HEADERS})
target_link_libraries (ATKDistortion_test ATKDistortion ATKIO ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKDistortion ATKDistortion_test --log_level=message)
endif(LIBSNDFILE_FOUND)

