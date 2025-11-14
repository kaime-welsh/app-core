include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY "https://github.com/skypjack/entt"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(EnTT)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Source/*.cpp")
add_library(Core STATIC)

target_sources(Core PRIVATE ${SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_link_libraries(Core EnTT::EnTT)

target_include_directories(Core PUBLIC Source)
