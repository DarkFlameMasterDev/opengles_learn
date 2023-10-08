cmake_minimum_required(VERSION 3.22.1)


project("opengles3_0")

include_directories(
 include/
)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src _SRC_FILES)
add_library(cpp_libs SHARED
    ${_SRC_FILES})

target_link_libraries(cpp_libs
    android
    log
    EGL
    GLESv3)