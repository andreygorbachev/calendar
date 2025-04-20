cmake_minimum_required(VERSION 3.15)

project("fin-calendar" VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(GREGORIAN_CALENDAR_MINIMAL TRUE)

#find_package(Calendar)
include(FetchContent)
FetchContent_Declare(
  calendar
  GIT_REPOSITORY https://github.com/andreygorbachev/calendar.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(calendar)

add_subdirectory(business_day_convention)

#set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
#export(PACKAGE FinCalendar)
