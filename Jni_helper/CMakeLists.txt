project(NIInvocation)
cmake_minimum_required(VERSION 3.8)

include_directories(AFTER ${CMAKE_SOURCE_DIR}/include)
find_library(log-lib log REQUIRED)

# Native Library
# ==============

add_library(jenv SHARED "jnihelper.c")
target_link_libraries(jenv ${log-lib})
