/// \file badugi_evaluator_test.cpp
/// \date 2023-10-15
///
/// \brief This file contains tests for the badugi evaluator.

#include <MoonPoker/evaluators/badugi_evaluator.hpp>

#include <gtest/gtest.h>

// ======================= Local Definitions =========================
BadugiHandEvaluator evaluator;

// ====================== evaluateDugiLevel Tests =========================

TEST(dugiEval, levelOne_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Two, Card::Heart),
    Card(Card::Two, Card::Diamond),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 1);
}
TEST(dugiEval, levelOne_Kings_Test)
{
  std::vector<Card> hand = {
    Card(Card::King, Card::Spade),
    Card(Card::King, Card::Club),
    Card(Card::King, Card::Heart),
    Card(Card::King, Card::Diamond),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 1);
}
TEST(dugiEval, levelTwo_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Two, Card::Diamond),
    Card(Card::Two, Card::Spade),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 2);
}
TEST(dugiEval, levelTwo2_Test)
{
  std::vector<Card> hand = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Four, Card::Club),
    Card(Card::Queen, Card::Heart),
    Card(Card::Four, Card::Diamond),
    Card(Card::Four, Card::Spade),
    Card(Card::Four, Card::Heart),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 2);
}
TEST(dugiEval, levelThree_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Ten, Card::Heart),
    Card(Card::Two, Card::Spade),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 3);
}
TEST(dugiEval, levelThree2_Test)
{
  std::vector<Card> hand = {
    Card(Card::Five, Card::Spade),
    Card(Card::Five, Card::Club),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 3);
}
TEST(dugiEval, levelFour_Test)
{
  std::vector<Card> hand = {
    Card(Card::Five, Card::Spade),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 4);
}
TEST(dugiEval, levelFour2_Test)
{
  std::vector<Card> hand = {
    Card(Card::Eight, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 4);
}

// The following tests are much more complex than the code will ever
// run into in practice
TEST(dugiEval, level4_Hard_Test)
{
  std::vector<Card> hand = {
    Card(Card::Eight, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 4);
}
TEST(dugiEval, level4_Hard2_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Club),
    Card(Card::King, Card::Spade),
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Heart),
    Card(Card::Queen, Card::Club),
    Card(Card::Jack, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Jack, Card::Heart),
    Card(Card::Jack, Card::Club),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 4);
}
TEST(dugiEval, level1_Hard_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Nine, Card::Spade),
    Card(Card::Ten, Card::Spade),
    Card(Card::Jack, Card::Spade),
    Card(Card::Queen, Card::Spade),
    Card(Card::King, Card::Spade),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 1);
}
TEST(dugiEval, level2_Hard_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Three, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Nine, Card::Spade),
    Card(Card::Ten, Card::Spade),
    Card(Card::Jack, Card::Spade),
    Card(Card::Queen, Card::Spade),
    Card(Card::King, Card::Spade),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 2);
}
TEST(dugiEval, level3_Hard_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Three, Card::Diamond),
    Card(Card::Four, Card::Diamond),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Nine, Card::Spade),
    Card(Card::Ten, Card::Spade),
    Card(Card::Jack, Card::Spade),
    Card(Card::Queen, Card::Spade),
    Card(Card::King, Card::Heart),
  };
  EXPECT_EQ(evaluator.evaluateDugiLevel(hand), 3);
}

// ====================== validDugi Tests =========================

TEST(dugiEval, validDugi_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
  };
  std::set<int> tempSet;
  EXPECT_TRUE(evaluator.validDugi(hand, 1, tempSet));
}
TEST(dugiEval, validDugi_Test2)
{
  std::vector<Card> hand = {
    Card(Card::King, Card::Spade),
    Card(Card::Ace, Card::Heart),
  };
  std::set<int> tempSet;
  EXPECT_FALSE(evaluator.validDugi(hand, 1, tempSet));
}
TEST(dugiEval, validDugi_Test3)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Two, Card::Diamond),
    Card(Card::Two, Card::Spade),
  };
  std::set<int> tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 2, tempSet), false);
}
TEST(dugiEval, validDugi_Test5)
{
  std::vector<Card> hand = {
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  std::set<int> tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 3, tempSet), true);
}
TEST(dugiEval, validDugi_Test6)
{
  std::vector<Card> hand = {
    Card(Card::Five, Card::Spade),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  std::set<int> tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 4, tempSet), false);
}
TEST(dugiEval, validDugi_Test7)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  std::set<int> tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 4, tempSet), true);
}
TEST(dugiEval, validDugi_Test8)
{
  std::vector<Card> hand = {
    Card(Card::Eight, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Five, Card::Club),
    Card(Card::Six, Card::Club),
  };
  std::set<int> tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 4, tempSet), false);
}
TEST(dugiEval, validDugi_Test9)
{
  std::vector<Card> hand = {
    Card(Card::Eight, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Six, Card::Club),
  };
  std::set<int> tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 4, tempSet), false);
}
TEST(dugiEval, validDugi_Test10)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Ace, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Four, Card::Diamond),
  };
  std::set<int> tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 4, tempSet), true);
}
TEST(dugiEval, validDugi_Test11)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Ace, Card::Club),
    Card(Card::Three, Card::Heart),
    Card(Card::Three, Card::Diamond),
  };
  std::set<int> tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 4, tempSet), false);
}
TEST(dugiEval, validDugi_Test12)
{
  // EMPTY HAND
  std::vector<Card> hand;
  std::set<int>     tempSet;
  EXPECT_EQ(evaluator.validDugi(hand, 3, tempSet), false);
}

// ====================== evaluateHand Tests =========================

TEST(dugiEval, evaluateHand1_Test)
{
  std::vector<Card> hand = {
    Card(Card::Two, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Two, Card::Heart),
    Card(Card::Two, Card::Diamond),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 2);
}
TEST(dugiEval, evaluateHand2_Test)
{
  std::vector<Card> hand = {
    Card(Card::King, Card::Spade),
    Card(Card::King, Card::Club),
    Card(Card::King, Card::Heart),
    Card(Card::King, Card::Diamond),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 13);
}
TEST(dugiEval, evaluateHand3_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Two, Card::Diamond),
    Card(Card::Two, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 102);
}
TEST(dugiEval, evaluateHand4_Test)
{
  std::vector<Card> hand = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Four, Card::Club),
    Card(Card::Queen, Card::Heart),
    Card(Card::Four, Card::Diamond),
    Card(Card::Four, Card::Spade),
    Card(Card::Four, Card::Heart),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 412);
}
TEST(dugiEval, evaluateHand5_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Ten, Card::Heart),
    Card(Card::Two, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 10210);
}
TEST(dugiEval, evaluateHand6_Test)
{
  std::vector<Card> hand = {
    Card(Card::Five, Card::Spade),
    Card(Card::Five, Card::Club),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 50607);
}
TEST(dugiEval, evaluateHand7_Test)
{
  std::vector<Card> hand = {
    Card(Card::Five, Card::Spade),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 1050607);
}
TEST(dugiEval, evaluateHand8_Test)
{
  std::vector<Card> hand = {
    Card(Card::Eight, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 5060711);
}
TEST(dugiEval, evaluateHand9_Test)
{
  std::vector<Card> hand = {
    Card(Card::King, Card::Spade),
    Card(Card::Ace, Card::Club),
    Card(Card::Five, Card::Heart),
    Card(Card::Ten, Card::Diamond),
    Card(Card::Ace, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 1051013);
}
TEST(dugiEval, evaluateHand10_Test)
{
  std::vector<Card> hand = {
    Card(Card::Seven, Card::Diamond),
    Card(Card::Eight, Card::Heart),
    Card(Card::Jack, Card::Club),
    Card(Card::Jack, Card::Spade),
    Card(Card::Nine, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 7080911);
}
TEST(dugiEval, evaluateHand11_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::King, Card::Spade),
    Card(Card::Ten, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 107);
}
TEST(dugiEval, evaluateHand12_Test)
{
  std::vector<Card> hand = {
    Card(Card::Eight, Card::Club),
    Card(Card::King, Card::Diamond),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ten, Card::Heart),
    Card(Card::Ten, Card::Diamond),
    Card(Card::Ace, Card::Diamond),

  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 10810);
}
TEST(dugiEval, evaluateHand13_Test)
{
  std::vector<Card> hand = {
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Diamond),
    Card(Card::Seven, Card::Club),
    Card(Card::Ace, Card::Heart),
    Card(Card::Three, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 1030709);
}
// The following tests are much more complex than the code will ever
// run into in practice
TEST(dugiEval, evaluateHand14_Test)
{
  std::vector<Card> hand = {
    Card(Card::Eight, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Five, Card::Heart),
    Card(Card::Six, Card::Club),
    Card(Card::Seven, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 5060711);
}
TEST(dugiEval, evaluateHand15_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Club),
    Card(Card::King, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Club),
    Card(Card::Jack, Card::Spade),
    Card(Card::Jack, Card::Club),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 11112);
}
TEST(dugiEval, evaluateHand16_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Three, Card::Heart),
    Card(Card::Four, Card::Club),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Eight, Card::Heart),
    Card(Card::Nine, Card::Club),
    Card(Card::Ten, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 1020304);
}
TEST(dugiEval, evaluateHand17_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Nine, Card::Spade),
    Card(Card::Ten, Card::Spade),
    Card(Card::Jack, Card::Spade),
    Card(Card::Queen, Card::Spade),
    Card(Card::King, Card::Spade),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 1);
}
TEST(dugiEval, evaluateHand18_Test)
{
  std::vector<Card> hand = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Three, Card::Diamond),
    Card(Card::Four, Card::Diamond),
    Card(Card::Five, Card::Spade),
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Queen, Card::Spade),
    Card(Card::King, Card::Heart),
  };
  long long result = evaluator.evaluateHand(hand);

  EXPECT_EQ(result, 10213);
}
