add_library(calendar INTERFACE
  weekend.h
  period.h
  schedule.h
  calendar.h
  annual_holiday_interface.h
  annual_holidays.h
  business_day_convention_interface.h
  business_day_conventions.h
  ics_parser.h
)

target_include_directories(calendar INTERFACE .)
