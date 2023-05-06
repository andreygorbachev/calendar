add_library(calendar INTERFACE
  calendar.h
  holiday.h
  business_days.h
)

target_include_directories(calendar INTERFACE .)
