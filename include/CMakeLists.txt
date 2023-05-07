add_library(calendar INTERFACE
  calendar.h
  holiday.h
  business_days.h
  ics_parser.h
)

target_include_directories(calendar INTERFACE .)
