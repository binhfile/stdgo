cmake_minimum_required(VERSION 2.8)
project(unittest)

# source
aux_source_directory(. SRC_LIST)
set (CMAKE_CXX_FLAGS "")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# googletest
include_directories("${GTEST_DIR}")
include_directories("${GTEST_DIR}/include")
# mode
if ("${MODE}" STREQUAL "")
    set (MODE "all")
endif()
string (TOUPPER ${MODE} MODE)
message ("MODE: ${MODE}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTDGO_UNITTEST -DSTDGO_UNITTEST_${MODE}")

# application
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(${PROJECT_NAME} ${SRC_LIST} "${GTEST_DIR}/src/gtest-all.cc")