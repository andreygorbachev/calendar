project("${PROJECT_NAME}_test" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  static_test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar_static-data
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
