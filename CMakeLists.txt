cmake_minimum_required(VERSION 3.16)
project(Game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Core)
add_subdirectory(Plugins/RaylibPlugin)
add_subdirectory(App)
