
FILE(GLOB_RECURSE
    ATK_IO_TEST_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_IO_TEST_HEADERS
    *.h
)

if(LIBSNDFILE_FOUND)
FILE(GLOB_RECURSE
    ATK_IO_LIBSNDFILE_TEST_SRC
    libsndfile/*.cpp
)

FILE(GLOB_RECURSE
    ATK_IO_LIBSNDFILE_TEST_HEADERS
    libsndfile/*.h
)
endif(LIBSNDFILE_FOUND)


include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKIO_test
    ${ATK_IO_TEST_SRC} ${ATK_IO_TEST_HEADERS}
    ${ATK_IO_LIBSNDFILE_TEST_SRC} ${ATK_IO_LIBSNDFILE_TEST_HEADERS}
)
target_link_libraries (ATKIO_test ATKIO ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(AudioTKIO ATKIO_test --log_level=message)

