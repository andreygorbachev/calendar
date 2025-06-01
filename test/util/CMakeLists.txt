project(calendar-util-test)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

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
