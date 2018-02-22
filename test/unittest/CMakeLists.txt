cmake_minimum_required(VERSION 3.0.2)
project(unittest)

# source
include_directories(../../include)
aux_source_directory(../../src/plot SRC_LIST)

# testcase
aux_source_directory(. SRC_LIST)
aux_source_directory(plot SRC_LIST)


set (CMAKE_CXX_FLAGS "")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
else()

endif()
# googletest
include_directories("${GTEST_DIR}")
include_directories("${GTEST_DIR}/include")
# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

# mode
if ("${MODE}" STREQUAL "")
    set (MODE "all")
endif()
string (TOUPPER ${MODE} MODE)
message ("MODE: ${MODE}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTDGO_UNITTEST -DSTDGO_UNITTEST_${MODE}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -DSTDGO_ENABLE_PLOT \
    -DSTDGO_ENABLE_PLOT_BACKEND_QT")
# application
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(${PROJECT_NAME} ${SRC_LIST} "${GTEST_DIR}/src/gtest-all.cc")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    target_link_libraries(${PROJECT_NAME} pthread rt)
endif()
# Qt
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)
