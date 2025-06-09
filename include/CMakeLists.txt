project("calendar")

add_subdirectory(util)

add_library(${PROJECT_NAME} INTERFACE
  weekend.h
  schedule.h
  calendar.h
  annual_holiday_interface.h
  annual_holidays.h
  business_day_adjuster_interface.h
  business_day_adjusters.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

target_link_libraries(${PROJECT_NAME} INTERFACE
  calendar-util
)

#export(TARGETS calendar NAMESPACE Calendar:: FILE CalendarConfig.cmake)
