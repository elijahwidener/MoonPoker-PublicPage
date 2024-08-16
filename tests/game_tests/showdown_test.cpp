/// \file showdown_test.cpp
/// \date 2023-12-14
///
/// \brief This file contains tests for the showdown method of all games
/// @note to be expanded on each time a new game is added, ensuring all games
/// showdown correctly.

#include <MoonPoker/games/no_limit_holdem.hpp>
#include <gtest/gtest.h>
/*
// ==================== Texas Hold'em ====================
TEST(showdown, SingleWinner_Test)
{
  // Create a hand evaluator and set up the pots
  Deck                                             deck;
  NoLimitHoldem                                    game(0, 10, 20);
  std::vector<std::pair<int, std::vector<Player>>> pots;
  // Create some players with 1000 chips
  Player Alice(1000);
  Player Bob(1000);
  Player Charlie(1000);

  pots.push_back({
    100, {Alice, Bob, Charlie}
  });

  // Deal the players and the game their cards
  Alice.dealCards(2, &deck);
  Bob.dealCards(2, &deck);
  Charlie.dealCards(2, &deck);
  for (int i = 0; i < 5; i++) {
    game.dealCardToBoard();
  }

  // Call the showdown function
  game.showdown();

  // Check the results
  ASSERT_EQ(100, pots[0].second[0].getStack()); // Alice wins the entire pot
  ASSERT_EQ(0, pots[0].second[1].getStack());   // Bob loses
  ASSERT_EQ(0, pots[0].second[2].getStack());   // Charlie loses
}
/*
TEST(showdown, MultipleWinners_Test)
{
  // Create a hand evaluator and set up the pots
  HandEvaluator                                    evaluator;
  std::vector<std::pair<int, std::vector<Player>>> pots;
  pots.push_back({
    200,
    {Player("Alice", Hand({Card("A", "Spades"), Card("K", "Spades")})),
      Player("Bob", Hand({Card("A", "Hearts"), Card("K", "Hearts")})),
      Player("Charlie", Hand({Card("Q", "Diamonds"), Card("Q", "Clubs")}))}
  });

  // Call the showdown function
  CommunityCard::showdown(evaluator, pots);

  // Check the results
  ASSERT_EQ(100, pots[0].second[0].getStack()); // Alice and Bob split the pot
  ASSERT_EQ(100, pots[0].second[1].getStack()); // Alice and Bob split the pot
  ASSERT_EQ(0, pots[0].second[2].getStack());   // Charlie loses
}
*/