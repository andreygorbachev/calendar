project("calendar")

add_library(${PROJECT_NAME} INTERFACE
  weekend.h
  period.h
  time_series.h
  schedule.h
  calendar.h
  annual_holiday_interface.h
  annual_holidays.h
  business_day_convention_interface.h
  business_day_conventions.h
  calendars.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)
