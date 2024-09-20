cmake_minimum_required(VERSION 3.15)

project("calendar" VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

enable_testing()

add_subdirectory(include)
add_subdirectory(test)
add_subdirectory(performance)
add_subdirectory(example)

#set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
#export(PACKAGE Calendar)
