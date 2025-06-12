cmake_minimum_required(VERSION 3.15)

project("calendar" VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_subdirectory(include)

if(NOT GREGORIAN_CALENDAR_MINIMAL)

	enable_testing()

	add_subdirectory(test)
	add_subdirectory(performance)
	add_subdirectory(example)

endif()

#set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
#export(PACKAGE Calendar)
