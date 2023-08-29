project(caller)
cmake_minimum_required(VERSION 3.8)

include_directories(AFTER ${CMAKE_SOURCE_DIR}/include)
find_library(log-lib log REQUIRED)

# Native Library
# ==============

add_executable(caller "caller.c")
add_library(jenv SHARED "jnihelper.c")
# set_property(TARGET fuzz APPEND_STRING PROPERTY LINK_FLAGS " -Wl,-rpath=$ORIGIN")
target_link_libraries(caller jenv)
