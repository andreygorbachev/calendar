project("business-day-convention")

add_library(${PROJECT_NAME} INTERFACE
  no_adjustment.h
  following.h
  preceding.h
  modified_following.h
  modified_preceding.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)

export(TARGETS business-day-convention NAMESPACE BusinessDayConvention:: FILE BusinessDayConventionConfig.cmake)
