project("Countries_example")

add_library(${PROJECT_NAME} INTERFACE
  calendars.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)
