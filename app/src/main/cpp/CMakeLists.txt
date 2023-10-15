cmake_minimum_required(VERSION 3.22.1)


project("opengles3_0")

include_directories(
    src/
)

file(GLOB src_files
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/sample/*.cpp)

message("${src_files}")

add_library(cpp_libs SHARED
    ${src_files})

target_link_libraries(cpp_libs
    android
    log
    EGL
    GLESv3)