add_library(calendar INTERFACE
  weekend.h
  calendar.h
  holiday.h
  business_days.h
  business_day_convention.h
  ics_parser.h
)

target_include_directories(calendar INTERFACE .)
