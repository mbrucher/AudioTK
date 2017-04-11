
FILE(GLOB_RECURSE
    ATK_DYNAMIC_PROFILE_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_DYNAMIC_PROFILE_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKDynamic_profile ${ATK_DYNAMIC_PROFILE_SRC} ${ATK_DYNAMIC_PROFILE_HEADERS} ${NATVIS_FILE})
target_link_libraries (ATKDynamic_profile ATKDynamic ATKTools ATKMock ATKCore)

set_target_properties (ATKDynamic_profile PROPERTIES
    FOLDER Profling
)
