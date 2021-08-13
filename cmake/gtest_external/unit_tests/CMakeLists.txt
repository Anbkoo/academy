enable_testing()
set (This gtest_cmake)

add_executable(
  ${This}
  test_fizz_buzz.cpp
)

target_link_libraries(
  ${This}
  fizzBuzz
  gtest_main
)