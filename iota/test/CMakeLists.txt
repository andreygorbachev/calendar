project(calendar-iota-test)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  iota.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar-iota
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
