project(business-day-convention-test)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  no_adjustment.cpp
  following.cpp
  preceding.cpp
  modified_following.cpp
  modified_preceding.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  business-day-convention
  calendar
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
