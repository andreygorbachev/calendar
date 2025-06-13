project("${PROJECT_NAME}-test" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  period.cpp
  iota.cpp
  time_series.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar-util
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
