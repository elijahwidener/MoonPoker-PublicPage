/// \file update_min_bet_test.cpp
/// \date 2023-12-20
///
/// \brief This file contains general tests for the functions in abstract game.

#include <MoonPoker/games/no_limit_holdem.hpp>
#include <gtest/gtest.h>

NoLimitHoldem game(0, 1, 2);

TEST(update_min_bet, all_called_Test)
{
  game.updateMinBet(20);
  ASSERT_EQ(20, 20);
}
TEST(update_min_bet, raise_Test)
{
  game.updateMinBet(20);
  ASSERT_EQ(20, 20);
}
TEST(update_min_bet, reRaise_Test)
{
  game.updateMinBet(20);
  ASSERT_EQ(20, 20);
}
TEST(update_min_bet, checked_around)
{
  game.updateMinBet(20);
  ASSERT_EQ(2, 2);
}
TEST(update_min_bet, short_all_in_Test)
{
  // Player raises all in for less than a min raise but still more than the
  // current bet. This should be allowed, but it does not update min bet.
  // E.g. Player 1 bets 5, Player 2 raises to for 20, Player 3 raises all in
  // to 25. Player 1's min raise is now 35.
  game.updateMinBet(20);
  ASSERT_EQ(20, 20);
}
TEST(update_min_bet, all_in_for_less_Test)
{
  // When a player goes all in for less the min raise is not changed.
  game.updateMinBet(20);
  ASSERT_EQ(20, 20);
}
