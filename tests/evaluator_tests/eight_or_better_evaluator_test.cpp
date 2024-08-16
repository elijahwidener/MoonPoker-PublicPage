/// \file eight_or_better_evaluator_test.cpp
/// \date 2023-11-09
///
/// \brief This file contains tests for the eight or better evaluator.

#include <MoonPoker/evaluators/eight_or_better_evaluator.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// ======================= Global Definitions =========================
EightOrBetterEvaluator eightOrBetterEvaluator;
// ====================== eightOrBetter Tests =========================

TEST(eightOrBetter, basic_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::King, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), 806050302);
}
TEST(eightOrBetter, basicAce_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::King, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), 605030201);
}
TEST(eightOrBetter, pair_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::King, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), 806050302);
}
TEST(eightOrBetter, straight_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::King, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), 605040302);
}
TEST(eightOrBetter, flush_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::King, Card::Diamond),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), 806050302);
}
TEST(eightOrBetter, manyPairs_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::King, Card::Diamond),

    Card(Card::Two, Card::Club),
    Card(Card::Three, Card::Diamond),
    Card(Card::Eight, Card::Club),
    Card(Card::Five, Card::Club),
    Card(Card::Six, Card::Club),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), 806050302);
}
TEST(eightOrBetter, trips_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
    Card(Card::Six, Card::Heart),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), 806050302);
}
TEST(eightOrBetter, comparison_Test)
{
  std::vector<Card> losingHand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  std::vector<Card> winningHand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  long long losingInt  = eightOrBetterEvaluator.evaluateHand(losingHand);
  long long winningInt = eightOrBetterEvaluator.evaluateHand(winningHand);

  // Winning hands are lower than losing hands
  EXPECT_LT(winningInt, losingInt);
}
TEST(eightOrBetter, comparison_Test2)
{
  std::vector<Card> losingHand = {
    Card(Card::Eight, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Four, Card::Spade),
  };

  std::vector<Card> winningHand = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Six, Card::Club),
    Card(Card::Five, Card::Heart),
    Card(Card::Four, Card::Diamond),
    Card(Card::Three, Card::Spade),
  };

  long long losingInt  = eightOrBetterEvaluator.evaluateHand(losingHand);
  long long winningInt = eightOrBetterEvaluator.evaluateHand(winningHand);

  EXPECT_LT(winningInt, losingInt);
}
TEST(eightOrBetter, large_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Jack, Card::Heart),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::King, Card::Spade),
    Card(Card::Queen, Card::Club),
    Card(Card::Nine, Card::Heart),
    Card(Card::Ten, Card::Diamond),
    Card(Card::Two, Card::Club),
    Card(Card::Ace, Card::Spade),
    Card(Card::Queen, Card::Heart),
    Card(Card::Nine, Card::Heart),
    Card(Card::Four, Card::Diamond),
    Card(Card::Five, Card::Club),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), 504030201);
}
TEST(eightOrBetter, noLow_Test)
{
  std::vector<Card> hand = {
    Card(Card::Nine, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Four, Card::Spade),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), -1);
}
TEST(eightOrBetter, noLow_Test2)
{
  std::vector<Card> hand = {
    Card(Card::Three, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Two, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Four, Card::Spade),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), -1);
}
TEST(eightOrBetter, noLow_Test3)
{
  std::vector<Card> hand = {
    Card(Card::King, Card::Spade),
    Card(Card::Queen, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Five, Card::Spade),
    Card(Card::Four, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Ten, Card::Diamond),
    Card(Card::Five, Card::Spade),
  };

  EXPECT_EQ(eightOrBetterEvaluator.evaluateHand(hand), -1);
}
