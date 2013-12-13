
FILE(GLOB_RECURSE
    ATK_CORE_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_CORE_HEADER
    *.h
)

add_library(ATKCore
    ${ATK_CORE_SRC} ${ATK_CORE_SRC}
)

