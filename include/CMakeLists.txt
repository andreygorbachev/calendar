add_library(calendar INTERFACE
  weekend.h
  holiday_schedule.h
  calendar.h
  holiday.h
  business_day_convention_interface.h
  business_day_conventions.h
  ics_parser.h
)

target_include_directories(calendar INTERFACE .)
