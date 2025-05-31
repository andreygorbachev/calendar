project("calendar-util")

add_library(${PROJECT_NAME} INTERFACE
  iota.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS calendar-util NAMESPACE Calendar::Util:: FILE CalendarUtilConfig.cmake)
