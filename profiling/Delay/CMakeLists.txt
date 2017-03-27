
FILE(GLOB_RECURSE
    ATK_DELAY_PROFILE_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_DELAY_PROFILE_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKDelay_profile ${ATK_DELAY_PROFILE_SRC} ${ATK_DELAY_PROFILE_HEADERS} ${NATVIS_FILE})
target_link_libraries (ATKDelay_profile ATKDelay ATKTools ATKMock ATKCore)

set_target_properties (ATKDelay_profile PROPERTIES
    FOLDER Profling
)
