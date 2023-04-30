add_library(calendar INTERFACE
  calendar.h
  holiday.h
)

target_include_directories(calendar INTERFACE .)
