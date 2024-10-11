cmake_minimum_required(VERSION 3.20)

project(RGL)

add_subdirectory(vendor/glfw)

add_executable(RGL src/glad.c src/main.c)
target_include_directories(RGL PRIVATE include vendor/glfw/include)
target_link_libraries(RGL glfw)