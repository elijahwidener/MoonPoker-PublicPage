/// \file close_action_test.cpp
/// \date 2023-12-16
///
/// \brief This file contains general tests for the functions in abstract game.

#include <MoonPoker/games/no_limit_holdem.hpp>
#include <gtest/gtest.h>

NoLimitHoldem testingGame(1, 1, 1);

TEST(close_action, all_called_Test)
{
  ASSERT_TRUE(testingGame.closeAction(10));
}
TEST(close_action, all_all_in_Test)
{
  ASSERT_TRUE(testingGame.closeAction(1000));
}
TEST(close_action, all_butOne_all_in_Test)
{
  ASSERT_TRUE(testingGame.closeAction(100));
}
TEST(close_action, checked_around)
{
  ASSERT_TRUE(testingGame.closeAction(0));
}
TEST(close_action, one_not_called_Test)
{
  ASSERT_FALSE(testingGame.closeAction(100));
}
TEST(close_action, many_not_called_Test)
{
  ASSERT_FALSE(testingGame.closeAction(100));
}
