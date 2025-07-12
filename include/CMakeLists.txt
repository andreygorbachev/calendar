# project "calendar"

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
  calendar_util
)

# should we consider .natvis file for Windows debugging? (would be cool to see business days as days not flags)

#export(TARGETS calendar NAMESPACE Calendar:: FILE CalendarConfig.cmake)
