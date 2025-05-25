project("calendar-iota")

add_library(${PROJECT_NAME} INTERFACE
  iota.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS calendar-iota NAMESPACE Calendar::Iota:: FILE CalendarIotaConfig.cmake)
