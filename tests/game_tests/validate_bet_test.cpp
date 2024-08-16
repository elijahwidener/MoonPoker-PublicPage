/// \file static_game_test.cpp
/// \date 2023-11-26
///
/// \brief This file contains general tests for the static functions in abstract game.

#include <MoonPoker/games/abstract_game.hpp>
#include <gtest/gtest.h>

TEST(bet_validation, FL_true_Test)
{
  ASSERT_TRUE(Game::validateBet(10, 10, 10));
}
TEST(bet_validation, false_under_Test)
{
  ASSERT_FALSE(Game::validateBet(9.99, 10, 10));
}
TEST(bet_validation, false_over_Test)
{
  ASSERT_FALSE(Game::validateBet(10.1, 10, 10));
}
TEST(bet_validation, false_min_GT_max_Test)
{
  ASSERT_FALSE(Game::validateBet(50.2, 100, 10));
}
TEST(bet_validation, true_short_all_in_Test)
{
  ASSERT_TRUE(Game::validateBet(50.129, 100, 50.129));
}
TEST(bet_validation, true_min_raise_Test)
{
  ASSERT_TRUE(Game::validateBet(50.129, 50.129, 5000));
}
