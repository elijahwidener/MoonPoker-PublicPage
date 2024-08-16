/// \file lowball_evaluator_test.cpp
/// \date 2023-010-16
///
/// \brief This file contains tests for the lowball evaluator.

#include <MoonPoker/evaluators/lowball_evaluator.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// ======================= Global Definitions =========================

LowballEvaluator lowballEvaluator;

// ====================== classicLowball Tests =========================
TEST(classicLowball, basic_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 806050302);
}
TEST(classicLowball, basicAce_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 605030201);
}
TEST(classicLowball, straight_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 605040302);
}
TEST(classicLowball, flush_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 806050302);
}
TEST(classicLowball, pair_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 806050302);
}
TEST(classicLowball, manyPairs_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Three, Card::Diamond),
    Card(Card::Eight, Card::Club),
    Card(Card::Five, Card::Club),
    Card(Card::Six, Card::Club),
  };
  LowballEvaluator evaluator;

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 806050302);
}
TEST(classicLowball, trips_Test)
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

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 806050302);
}
TEST(classicLowball, acePlusHigh_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::King, Card::Club),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Ten, Card::Spade),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 1312111001);
}
TEST(classicLowball, comparison_Test)
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

  long long losingInt  = lowballEvaluator.evaluateHand(losingHand);
  long long winningInt = lowballEvaluator.evaluateHand(winningHand);

  // Winning hands are lower than losing hands
  EXPECT_LT(winningInt, losingInt);
}
TEST(classicLowball, comparison_Test2)
{
  std::vector<Card> winningHand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Jack, Card::Heart),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  std::vector<Card> losingHand = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Jack, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  long long losingInt  = lowballEvaluator.evaluateHand(losingHand);
  long long winningInt = lowballEvaluator.evaluateHand(winningHand);

  EXPECT_LT(winningInt, losingInt);
}
TEST(classicLowball, comparison_Test3)
{
  std::vector<Card> losingHand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Eight, Card::Spade),
  };

  std::vector<Card> winningHand = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Six, Card::Club),
    Card(Card::Five, Card::Heart),
    Card(Card::Four, Card::Diamond),
    Card(Card::Three, Card::Spade),
  };

  long long losingInt  = lowballEvaluator.evaluateHand(losingHand);
  long long winningInt = lowballEvaluator.evaluateHand(winningHand);

  EXPECT_LT(winningInt, losingInt);
}
TEST(classicLowball, large_Test)
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

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 504030201);
}
TEST(classicLowball, largeComparison_Test2)
{
  std::vector<Card> winningHand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Club),
    Card(Card::Jack, Card::Heart),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::King, Card::Spade),
    Card(Card::Queen, Card::Club),
    Card(Card::Nine, Card::Heart),
    Card(Card::Ten, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  std::vector<Card> losingHand = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Jack, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Spade),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Heart),
  };

  long long losingInt  = lowballEvaluator.evaluateHand(losingHand);
  long long winningInt = lowballEvaluator.evaluateHand(winningHand);
  EXPECT_LT(winningInt, losingInt);
}
TEST(classicLowball, noFiveUnique_pair_Test)
{
  std::vector<Card> hand = {
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 2060030508);
}
TEST(classicLowball, noFiveUnique_pair_Test2)
{
  std::vector<Card> hand = {
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
    Card(Card::Seven, Card::Diamond),

  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 2030050607);
}
TEST(classicLowball, noFiveUnique_twoPair_Test)
{
  std::vector<Card> hand = {
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 3060300005);
}
TEST(classicLowball, noFiveUnique_twoPair_Test2)
{
  std::vector<Card> hand = {
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Diamond),

  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 3030100006);
}
TEST(classicLowball, noFiveUnique_trips_Test)
{
  std::vector<Card> hand = {
    Card(Card::Three, Card::Club),
    Card(Card::Eight, Card::Heart),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Club),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 4010000308);
}
TEST(classicLowball, noFiveUnique_trips_Test2)
{
  std::vector<Card> hand = {
    Card(Card::King, Card::Club),
    Card(Card::King, Card::Spade),
    Card(Card::King, Card::Heart),
    Card(Card::Three, Card::Club),
    Card(Card::Two, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Two, Card::Club),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 4020000313);
}
TEST(classicLowball, noFiveUnique_quads_Test)
{
  std::vector<Card> hand = {
    Card(Card::Three, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Club),
  };

  EXPECT_EQ(lowballEvaluator.evaluateHand(hand), 5010000003);
}
TEST(classicLowball, noFiveUnique_Comparison_Test)
{
  std::vector<Card> winningHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Eight, Card::Heart),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
  };

  std::vector<Card> losingHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
  };

  int losingHandInt  = lowballEvaluator.evaluateHand(losingHand);
  int winningHandInt = lowballEvaluator.evaluateHand(winningHand);

  EXPECT_LT(winningHandInt, losingHandInt);
}
TEST(classicLowball, noFiveUnique_Comparison_Test2)
{
  std::vector<Card> winningHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Three, Card::Heart),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
  };

  std::vector<Card> losingHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
  };

  int losingHandInt  = lowballEvaluator.evaluateHand(losingHand);
  int winningHandInt = lowballEvaluator.evaluateHand(winningHand);

  EXPECT_LT(winningHandInt, losingHandInt);
}
TEST(classicLowball, noFiveUnique_Comparison_Test3)
{
  std::vector<Card> winningHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Three, Card::Diamond),
    Card(Card::Three, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Five, Card::Diamond),
    Card(Card::Ace, Card::Diamond),
  };

  std::vector<Card> losingHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Six, Card::Spade),
    Card(Card::Six, Card::Diamond),
  };

  int losingHandInt  = lowballEvaluator.evaluateHand(losingHand);
  int winningHandInt = lowballEvaluator.evaluateHand(winningHand);

  EXPECT_LT(winningHandInt, losingHandInt);
}
TEST(classicLowball, noFiveUnique_Comparison_Test4)
{
  std::vector<Card> winningHand = {
    Card(Card::King, Card::Club),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ten, Card::Diamond),
    Card(Card::Nine, Card::Diamond),
    Card(Card::Eight, Card::Spade),
    Card(Card::Seven, Card::Diamond),
  };

  std::vector<Card> losingHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Heart),
    Card(Card::Five, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Diamond),
  };

  int losingHandInt  = lowballEvaluator.evaluateHand(losingHand);
  int winningHandInt = lowballEvaluator.evaluateHand(winningHand);

  EXPECT_LT(winningHandInt, losingHandInt);
}
TEST(classicLowball, noFiveUnique_Comparison_Test5)
{
  std::vector<Card> winningHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Eight, Card::Heart),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Six, Card::Diamond),
  };

  std::vector<Card> losingHand = {
    Card(Card::Three, Card::Club),
    Card(Card::Two, Card::Diamond),
    Card(Card::Two, Card::Spade),
    Card(Card::King, Card::Spade),
    Card(Card::King, Card::Diamond),
  };

  int losingHandInt  = lowballEvaluator.evaluateHand(losingHand);
  int winningHandInt = lowballEvaluator.evaluateHand(winningHand);

  EXPECT_LT(winningHandInt, losingHandInt);
}
