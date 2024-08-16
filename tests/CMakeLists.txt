# tests/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

include(external)
include(GoogleTest)

enable_testing()

add_executable(general_test)
target_sources(general_test PRIVATE general.cpp)
target_link_libraries(general_test PRIVATE external::gtest)
gtest_discover_tests(general_test)

# Helper function to add a moonpoker test executable.
function(add_test_moonpoker name)
  add_executable(${name}_test)
  target_sources(${name}_test PRIVATE ${ARGN})
  target_link_libraries(${name}_test PRIVATE external::gtest moon_poker_core)
  gtest_discover_tests(${name}_test)
endfunction()

add_test_moonpoker(standard_evaluator evaluator_tests/standard_evaluator_test.cpp)
add_test_moonpoker(badugi_evaluator evaluator_tests/badugi_evaluator_test.cpp)
add_test_moonpoker(lowball_evaluator evaluator_tests/lowball_evaluator_test.cpp)
add_test_moonpoker(omaha_eight_evaluator evaluator_tests/omaha_eight_evaluator_test.cpp)
add_test_moonpoker(eight_or_better_evaluator evaluator_tests/eight_or_better_evaluator_test.cpp)
add_test_moonpoker(omaha_evaluator evaluator_tests/omaha_evaluator_test.cpp)
add_test_moonpoker(bet_validation game_tests/validate_bet_test.cpp)
add_test_moonpoker(showdown game_tests/showdown_test.cpp)
add_test_moonpoker(close_action game_tests/close_action_test.cpp)
add_test_moonpoker(update_min_bet game_tests/update_min_bet_test.cpp)



