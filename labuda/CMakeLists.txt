cmake_minimum_required (VERSION 3.29)
project (labuda)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-std=c++20")

add_subdirectory(user-mgmt)
add_subdirectory(type-list)
add_subdirectory(type-map)
add_subdirectory(logging)
add_subdirectory(trophy)
add_subdirectory(mix-in)
add_subdirectory(bridge-set)
add_subdirectory(expression-factory)

enable_testing()
# add_subdirectory(tests)
