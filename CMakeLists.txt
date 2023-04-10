cmake_minimum_required(VERSION 3.8)

project("calendar" VERSION 0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_subdirectory(include)
add_subdirectory(test)
