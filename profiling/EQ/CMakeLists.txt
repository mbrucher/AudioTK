
FILE(GLOB_RECURSE
    ATK_EQ_PROFILE_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_EQ_PROFILE_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKEQ_profile ${ATK_EQ_PROFILE_SRC} ${ATK_EQ_PROFILE_HEADERS} ${NATVIS_FILE})
target_link_libraries (ATKEQ_profile ATKEQ ATKTools ATKMock ATKCore)

set_target_properties (ATKEQ_profile PROPERTIES
    FOLDER Profling
)
