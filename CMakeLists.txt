cmake_minimum_required(VERSION 3.25)
project(mtpc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#find_package(jsoncpp REQUIRED)

include_directories(external/stb)
include_directories(external/nlohmannjson/include)
#include_directories(${JSONCPP_INCLUDE_DIRS})  # Add this line

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE HEADERSPP ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

add_executable(mtpc ${SOURCES} ${HEADERS} ${HEADERSPP})

#target_link_libraries(mtpc PRIVATE jsoncpp)
