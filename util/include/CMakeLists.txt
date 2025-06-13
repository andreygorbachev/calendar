# project "calendar_util"

add_library(${PROJECT_NAME} INTERFACE
  period.h
  iota.h
  time_series.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

#export(TARGETS calendar-util NAMESPACE Calendar::Util:: FILE CalendarUtilConfig.cmake)
