file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Source/*.cpp")

add_executable(App)
target_sources(App PRIVATE ${SOURCES})

target_link_libraries(App Core)
target_link_libraries(App RaylibPlugin)
target_include_directories(App PRIVATE Source)

set_target_properties(App PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/App"
)
