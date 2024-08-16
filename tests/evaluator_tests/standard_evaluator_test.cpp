/// \file standard_evaluator_test.cpp
/// \date 2023-10-19
///
/// \brief This file contains general tests for the NLH game.

#include <MoonPoker/evaluators/standard_evaluator.hpp>
#include <gtest/gtest.h>

#include <vector>

StandardEvaluator handEvaluator;

TEST(hand_evaluator_basic, Test1)
{
  EXPECT_EQ(1, 1);
}

// ========================[ getRank Tests ]========================

TEST(HandEvaluatorGeneral, GetRanks)
{

  Card card(Card::Ace, Card::Heart);
  EXPECT_EQ(card.getRank(), 14);

  Card card2(Card::Two, Card::Spade);
  EXPECT_EQ(card2.getRank(), 2);

  Card card3(Card::Jack, Card::Diamond);
  EXPECT_EQ(card3.getRank(), 11);

  Card card4(Card::Queen, Card::Club);
  EXPECT_EQ(card4.getRank(), 12);

  Card card5(Card::King, Card::Spade);
  EXPECT_EQ(card5.getRank(), 13);

  Card card6(Card::Ace, Card::Heart);
  EXPECT_EQ(card6.getRank(), 14);

  Card card7(Card::Two, Card::Spade);
  EXPECT_EQ(card7.getRank(), 2);

  Card card8(Card::Jack, Card::Diamond);
  EXPECT_EQ(card8.getRank(), 11);

  Card card9(Card::Queen, Card::Club);
  EXPECT_EQ(card9.getRank(), 12);

  Card card10(Card::King, Card::Spade);
  EXPECT_EQ(card10.getRank(), 13);
}

// ========================[ getSuit Tests ]========================

TEST(getSuitTest, GeneralSuits)
{

  Card card(Card::Queen, Card::Club);
  EXPECT_EQ(card.getSuit(), Card::Club);

  Card card1(Card::Jack, Card::Diamond);
  EXPECT_EQ(card1.getSuit(), Card::Diamond);

  Card card2(Card::Two, Card::Spade);
  EXPECT_EQ(card2.getSuit(), Card::Spade);

  Card card3(Card::Ace, Card::Heart);
  EXPECT_EQ(card3.getSuit(), Card::Heart);

  Card card4(Card::Ace, Card::Club);
  EXPECT_EQ(card4.getSuit(), Card::Club);
}

// ========================[ kickers Tests ]========================
TEST(kickersTest, TestEmptyVector)
{
  std::vector<int> emptyVector;
  EXPECT_EQ(handEvaluator.kickers(emptyVector, 0), 0);
}

TEST(kickersTest, TestOneElement)
{
  std::vector<int> oneElementVector;
  oneElementVector.push_back(1);
  EXPECT_EQ(handEvaluator.kickers(oneElementVector, 0), 0);
}

TEST(kickersTest, TestTwoElements)
{
  std::vector<int> twoElementVector;
  twoElementVector.push_back(1);
  twoElementVector.push_back(2);
  EXPECT_EQ(handEvaluator.kickers(twoElementVector, 0), 0);
}

TEST(kickersTest, TestThreeElements)
{
  std::vector<int> threeElementVector = {1, 2, 3};
  EXPECT_EQ(handEvaluator.kickers(threeElementVector, 0), 0);
}

TEST(kickersTest, TestZeroKickers)
{
  std::vector<int> unique_Ranks = {4};
  EXPECT_EQ(handEvaluator.kickers(unique_Ranks, 0), 0);
}

// 4 of hearts, 2 of spades
// 4 * 100 + 2 = 402
TEST(kickersTest, TestAllRanksUsed)
{
  std::vector<int> unique_Ranks = {4, 2};
  EXPECT_EQ(handEvaluator.kickers(unique_Ranks, 2), 402);
}

// ========================[ isStraight Tests ]========================
TEST(isStraightTest, NoStraight)
{
  std::vector<int> uniqueRanks = {2, 4, 5, 8, 10};
  EXPECT_EQ(handEvaluator.isStraight(uniqueRanks), 0);
}

TEST(isStraightTest, FiveCardStraight)
{
  std::vector<int> uniqueRanks = {2, 3, 4, 5, 6};
  EXPECT_EQ(handEvaluator.isStraight(uniqueRanks), 6);
}

TEST(isStraightTest, SixCardStraight)
{
  std::vector<int> uniqueRanks = {3, 4, 5, 6, 7, 8};
  EXPECT_EQ(handEvaluator.isStraight(uniqueRanks), 8);
}

TEST(isStraightTest, WheelStraight)
{
  std::vector<int> uniqueRanks = {2, 3, 4, 5, 14};
  EXPECT_EQ(handEvaluator.isStraight(uniqueRanks), 5);
}

TEST(isStraightTest, MultipleStraights)
{
  std::vector<int> uniqueRanks = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12};
  EXPECT_EQ(handEvaluator.isStraight(uniqueRanks), 12);
}

// ========================[ isFlush Tests ]========================
// A flush is when we have 5+ cards of the same suit
TEST(isFlushTest, NoFlush)
{
  std::vector<Card> handPlusBoard = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Spade),
    Card(Card::Four, Card::Diamond),
    Card(Card::Jack, Card::Club),
    Card(Card::Ace, Card::Heart)};

  bool result = handEvaluator.isFlush(handPlusBoard);

  ASSERT_FALSE(result);
}

TEST(isFlushTest, ExactFlush)
{
  std::vector<Card> handPlusBoard = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Four, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart)};

  EXPECT_EQ(handEvaluator.isFlush(handPlusBoard), true);
}

TEST(isFlushTest, OverFlush)
{
  std::vector<Card> handPlusBoard = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Four, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Three, Card::Heart),
    Card(Card::Eight, Card::Heart),
    Card(Card::Two, Card::Heart),
  };

  EXPECT_EQ(handEvaluator.isFlush(handPlusBoard), true);
}

TEST(isFlushTest, ExactBigHand)
{
  std::vector<Card> handPlusBoard = {
    Card(Card::King, Card::Spade),
    Card(Card::Queen, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Jack, Card::Spade),
    Card(Card::Ace, Card::Spade),
    Card(Card::Three, Card::Heart),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Two, Card::Club),
    Card(Card::Five, Card::Club),
  };

  EXPECT_EQ(handEvaluator.isFlush(handPlusBoard), true);
}

// ========================[ evaluateHand Tests ]========================
// RoyalFlush
// StraightFlush
// FourOfaKind
// FullHouse
// Flush
// Straight
// ThreeOfAKind
// TwoPair
// Pair
// HighCard

TEST(evaluateHandResult, RoyalFlush)
{
  // Royal flush because all cards are of the same suit and the ranks are
  // 10, J,
  // Q, K, A

  std::vector<Card> playerCards = {
    Card(Card::Ace, Card::Diamond),
    Card(Card::King, Card::Diamond),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Queen, Card::Diamond),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Ten, Card::Diamond)};

  // call evaluateHand function
  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  // expected result: 90000000000
  long long expected = 90000000014;

  ASSERT_EQ(result, expected);
}

TEST(evaluateHandResult, StraightFlush)
{
  std::vector<Card> playerCards = {
    Card(Card::Four, Card::Diamond),
    Card(Card::Five, Card::Diamond),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Three, Card::Diamond),
    Card(Card::Two, Card::Diamond),
    Card(Card::Six, Card::Diamond)};

  // call evaluateHand function
  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  // expected result:
  long long expected = 90000000006;

  ASSERT_EQ(result, expected);
}

TEST(evaluateHandResult, FourOfaKind)
{

  std::vector<Card> playerCards = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
    Card(Card::Eight, Card::Spade)};

  // call evaluateHand function
  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  // expected result: 80000000000 + (14 * 100) + 8 = 80000001408
  long long expected = 80000001408;

  // assert
  ASSERT_EQ(result, expected);
}

TEST(evaluateHandResult, FullHouse)
{
  // create cards: Player holds 7 of Diamonds and 7 of Hearts
  // dealer holds 7 of Clubs, 3 of Spades, and 3 of Diamonds
  // the hand forms a Full House: 7s over 3s
  std::vector<Card> playerCards = {
    Card(Card::Seven, Card::Diamond),
    Card(Card::Seven, Card::Heart),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Seven, Card::Club),
    Card(Card::Three, Card::Spade),
    Card(Card::Three, Card::Diamond)};

  // call evaluateHand function
  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  // expected result: 70000000000 + (7 * 100) + 3 = 70000000703
  long long expected = 70000000703;

  // assert
  ASSERT_EQ(result, expected);
}

TEST(evaluateHandResult, Flush)
{
  std::vector<Card> playerCards = {
    Card(Card::Ace, Card::Diamond), Card(Card::King, Card::Diamond)};

  std::vector<Card> dealerCards = {
    Card(Card::Three, Card::Diamond),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Five, Card::Diamond)};

  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  long long expected = 61413080503;

  ASSERT_EQ(result, expected);
}

TEST(evaluateHandResult, Straight)
{
  std::vector<Card> playerCards = {
    Card(Card::Ten, Card::Diamond),
    Card(Card::Nine, Card::Spade),
    Card(Card::Eight, Card::Heart),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Seven, Card::Club), Card(Card::Six, Card::Diamond)};

  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  long long expected = 50000000010; // 50000000000 + 10 because 10 is the high
                                    // card in the straight

  ASSERT_EQ(result, expected);
}

// this one fails
TEST(evaluateHandResult, ThreeOfAKind)
{
  std::vector<Card> playerCards = {
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Ace, Card::Club),
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Diamond)};

  // call evaluateHand function
  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  // expected result: 40000000000 + (14 * 10000) + 0302 = 40000140302
  long long expected = 40000140302;

  // assert
  ASSERT_EQ(result, expected);
}

TEST(evaluateHandResult, TwoPair)
{
  std::vector<Card> playerCards = {
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Club),
    Card(Card::Two, Card::Spade),
    Card(Card::Three, Card::Diamond)};

  // call evaluateHand function
  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  // expected result:
  long long expected = 30000140203;

  // assert
  ASSERT_EQ(result, expected);
}

TEST(evaluateHandResult, OnePair)
{
  std::vector<Card> playerCards = {
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Diamond)};

  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  long long expected = 21400050403;

  ASSERT_EQ(result, expected);
}

TEST(evaluateHandResult, HighCard)
{
  std::vector<Card> playerCards = {
    Card(Card::King, Card::Diamond),
    Card(Card::Ace, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Diamond)};

  long long result = handEvaluator.evaluateHand(playerCards, dealerCards);

  long long expected = 1413050403;

  ASSERT_EQ(result, expected);
}

// ==================[ evaluateHand Comparison Tests ]==================
// 'x' indicates that a the combination has passed its test

// Royal Flush vs. Straight Flush     x
// Royal Flush vs. Four of a Kind     x
// Royal Flush vs. Full House         x
// Royal Flush vs. Flush              x
// Royal Flush vs. Straight           x
// Royal Flush vs. Three of a Kind    x
// Royal Flush vs. Two Pair           x
// Royal Flush vs. Pair               x
// Royal Flush vs. High Card          x
// Straight Flush vs. Four of a Kind  x
// Straight Flush vs. Full House      x
// Straight Flush vs. Flush           x
// Straight Flush vs. Straight        x
// Straight Flush vs. Three of a Kind x
// Straight Flush vs. Two Pair        x
// Straight Flush vs. Pair            x
// Straight Flush vs. High Card       x
// Four of a Kind vs. Full House      x
// Four of a Kind vs. Flush           x
// Four of a Kind vs. Straight        x
// Four of a Kind vs. Three of a Kind x
// Four of a Kind vs. Two Pair        x
// Four of a Kind vs. Pair            x
// Four of a Kind vs. High Card       x
// Full House vs. Flush		            x
// Full House vs. Straight            x
// Full House vs. Three of a Kind     x
// Full House vs. Two Pair            x
// Full House vs. Pair                x
// Full House vs. High Card           x
// Flush vs. Straight                 x
// Flush vs. Three of a Kind          x
// Flush vs. Two Pair                 x
// Flush vs. Pair                     x
// Flush vs. High Card                x
// Straight vs. Three of a Kind       x
// Straight vs. Two Pair              x
// Straight vs. Pair                  x
// Straight vs. High Card             x
// Three of a Kind vs. Two Pair       x
// Three of a Kind vs. Pair           x
// Three of a Kind vs. High Card      x
// Two Pair vs. Pair                  x
// Two Pair vs. High Card             x
// Pair vs. High Card                 x

TEST(evaluateHandComparison, RoyalFlush_vs_StraightFlush)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Ten, Card::Heart),
  };

  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FourOfaKind_vs_FullHouse)
{
  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
  };

  // Full House 1
  std::vector<Card> FullHouse1 = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Club),
    Card(Card::Three, Card::Club),
    Card(Card::Two, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
    Card(Card::Eight, Card::Spade)};

  long long winningHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(FullHouse1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Flush_vs_Straight)
{
  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };
  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Club),
    Card(Card::Eight, Card::Spade),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Five, Card::Spade),
  };

  long long winningHandResult = handEvaluator.evaluateHand(Flush1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, RoyalFlush_vs_FourOfaKind)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Ten, Card::Heart),
  };

  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Seven, Card::Diamond),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Seven, Card::Diamond),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, RoyalFlush_vs_FullHouse)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Ten, Card::Heart),
  };

  // Full House 1
  std::vector<Card> FullHouse1 = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Heart),
    Card(Card::Three, Card::Club),
    Card(Card::Two, Card::Club),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(FullHouse1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, RoyalFlush_vs_Flush)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Six, Card::Heart),
  };

  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult = handEvaluator.evaluateHand(Flush1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, RoyalFlush_vs_Straight)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Six, Card::Heart),
  };

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Club),
    Card(Card::Eight, Card::Spade),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, RoyalFlush_vs_ThreeOfAKind)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Six, Card::Heart),
  };

  // ThreeOfAKind
  std::vector<Card> ThreeOfAKind = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, RoyalFlush_vs_TwoPair)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Six, Card::Heart),
  };

  // Two Pair
  std::vector<Card> TwoPair = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Three, Card::Spade),
    Card(Card::Two, Card::Spade),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(TwoPair, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, RoyalFlush_vs_Pair)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Six, Card::Heart),
  };

  // Pair 1
  std::vector<Card> Pair1 = {
    Card(Card::Eight, Card::Club),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Two, Card::Diamond),
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult = handEvaluator.evaluateHand(Pair1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, RoyalFlush_vs_HighCard)
{
  // Royal Flush 1
  std::vector<Card> RoyalFlush1 = {
    Card(Card::King, Card::Heart),
    Card(Card::Queen, Card::Heart),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ace, Card::Heart),
    Card(Card::Six, Card::Heart),
  };

  // Highcard 1
  std::vector<Card> HighCard = {
    Card(Card::Seven, Card::Heart),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Queen, Card::Diamond),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Six, Card::Diamond),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(RoyalFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, StraightFlush_vs_FourOfaKind)
{
  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Four, Card::Diamond),
    Card(Card::Five, Card::Diamond),
  };

  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Three, Card::Diamond),
    Card(Card::Two, Card::Diamond),
    Card(Card::Six, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, StraightFlush_vs_FullHouse)
{
  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Four, Card::Diamond),
    Card(Card::Five, Card::Diamond),
  };

  // Full House 1
  std::vector<Card> FullHouse1 = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Club),
    Card(Card::Three, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Three, Card::Diamond),
    Card(Card::Two, Card::Diamond),
    Card(Card::Six, Card::Diamond)};

  long long winningHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(FullHouse1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, StraightFlush_vs_Flush)
{
  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards1);
  long long losingHandResult = handEvaluator.evaluateHand(Flush1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, StraightFlush_vs_Straight)
{
  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Club),
    Card(Card::Eight, Card::Spade),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, StraightFlush_vs_ThreeOfAKind)
{
  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  // Three of a kind 1
  std::vector<Card> ThreeOfAKind1 = {
    Card(Card::Eight, Card::Club),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Eight, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind1, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, StraightFlush_vs_TwoPair)
{
  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  // Two pair
  std::vector<Card> TwoPair = {
    Card(Card::Eight, Card::Club),
    Card(Card::Eight, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Two, Card::Club),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(TwoPair, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, StraightFlush_vs_Pair)
{
  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  // Pair
  std::vector<Card> Pair = {
    Card(Card::Eight, Card::Club),
    Card(Card::Eight, Card::Diamond),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Heart),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards1);
  long long losingHandResult = handEvaluator.evaluateHand(Pair, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, StraightFlush_vs_HighCard)
{
  // Straight Flush 1
  std::vector<Card> StraightFlush1 = {
    Card(Card::Six, Card::Spade),
    Card(Card::Seven, Card::Spade),
    Card(Card::Eight, Card::Spade),
    Card(Card::Four, Card::Spade),
    Card(Card::Five, Card::Spade),
  };

  // Highcard 1
  std::vector<Card> HighCard = {
    Card(Card::Seven, Card::Heart),
  };

  std::vector<Card> dealerCards1 = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Heart),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(StraightFlush1, dealerCards1);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards1);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FourOfaKind_vs_Flush)
{
  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
  };

  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Eight, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(Flush1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FourOfaKind_vs_Straight)
{
  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
  };

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Club),
    Card(Card::Eight, Card::Spade),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Eight, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FourOfaKind_vs_ThreeOfAKind)
{
  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
  };

  // ThreeOfAKind
  std::vector<Card> ThreeOfAKind = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Eight, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FourOfaKind_vs_TwoPair)
{
  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
  };

  // Two Pair
  std::vector<Card> TwoPair = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Six, Card::Heart),
    Card(Card::Six, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Eight, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(TwoPair, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FourOfaKind_vs_Pair)
{
  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
  };

  // Pair
  std::vector<Card> Pair = {
    Card(Card::Eight, Card::Club),
    Card(Card::Four, Card::Diamond),
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Heart),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(Pair, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FourOfaKind_vs_HighCard)
{
  // Four of a Kind 1
  std::vector<Card> FourOfaKind1 = {
    Card(Card::Ace, Card::Heart),
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Ace, Card::Club),
  };

  // HighCard
  std::vector<Card> HighCard = {
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Four, Card::Heart),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FourOfaKind1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FullHouse_vs_Flush)
{
  // Full House 1
  std::vector<Card> FullHouse1 = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Club),
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Diamond),
  };

  // Flush
  std::vector<Card> Flush = {
    Card(Card::Four, Card::Club),
    Card(Card::Nine, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Ace, Card::Club),
    Card(Card::Jack, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Eight, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FullHouse1, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(Flush, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FullHouse_vs_Straight)
{
  // Full House 1
  std::vector<Card> FullHouse1 = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Club),
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Diamond),
  };

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Club),
    Card(Card::Eight, Card::Spade),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Eight, Card::Diamond),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FullHouse1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FullHouse_vs_ThreeOfAKind)
{
  // Full House 1
  std::vector<Card> FullHouse1 = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Club),
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Diamond),
  };

  // ThreeOfAKind
  std::vector<Card> ThreeOfAKind = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Eight, Card::Diamond),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FullHouse1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FullHouse_vs_Pair)
{
  // Full House 1
  std::vector<Card> FullHouse1 = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Club),
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Diamond),
  };

  // Pair 1
  std::vector<Card> Pair1 = {
    Card(Card::Eight, Card::Club),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Two, Card::Diamond),
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Four, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FullHouse1, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(Pair1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, FullHouse_vs_HighCard)
{
  // Full House 1
  std::vector<Card> FullHouse1 = {
    Card(Card::Queen, Card::Spade),
    Card(Card::Queen, Card::Diamond),
    Card(Card::Queen, Card::Club),
    Card(Card::Three, Card::Club),
    Card(Card::Three, Card::Diamond),
  };

  // Pair 1
  std::vector<Card> HighCard = {
    Card(Card::Eight, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Heart),
    Card(Card::Ten, Card::Club),
    Card(Card::Four, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(FullHouse1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Flush_vs_Straight1)
{
  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Spade),
    Card(Card::Eight, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Four, Card::Spade),
  };

  long long winningHandResult = handEvaluator.evaluateHand(Flush1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Flush_vs_ThreeOfAKind)
{
  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };

  // Three of a kind 1
  std::vector<Card> ThreeOfAKind1 = {
    Card(Card::Eight, Card::Club),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Eight, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Nine, Card::Club),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Four, Card::Spade),
  };

  long long winningHandResult = handEvaluator.evaluateHand(Flush1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Flush_vs_TwoPair)
{
  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };

  // Two Pair
  std::vector<Card> TwoPair = {
    Card(Card::Eight, Card::Club),
    Card(Card::Eight, Card::Diamond),
    Card(Card::Four, Card::Diamond),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Four, Card::Heart),
    Card(Card::Ten, Card::Diamond),
    Card(Card::Three, Card::Diamond),
  };

  long long winningHandResult = handEvaluator.evaluateHand(Flush1, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(TwoPair, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Flush_vs_Pair)
{
  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };

  // Pair
  std::vector<Card> Pair = {
    Card(Card::Eight, Card::Club),
    Card(Card::Eight, Card::Diamond),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Heart),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult = handEvaluator.evaluateHand(Flush1, dealerCards);
  long long losingHandResult  = handEvaluator.evaluateHand(Pair, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Flush_vs_HighCard)
{
  // Flush 1
  std::vector<Card> Flush1 = {
    Card(Card::Four, Card::Club),
    Card(Card::Jack, Card::Club),
    Card(Card::Eight, Card::Club),
    Card(Card::Two, Card::Club),
    Card(Card::Nine, Card::Club),
  };

  // Highcard 1
  std::vector<Card> HighCard = {
    Card(Card::Seven, Card::Heart),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Heart),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult = handEvaluator.evaluateHand(Flush1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Straight_vs_ThreeOfAKind)
{

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Spade),
    Card(Card::Eight, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // ThreeOfAKind
  std::vector<Card> ThreeOfAKind = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Club),
    Card(Card::Five, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Four, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Straight_vs_TwoPair)
{

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Spade),
    Card(Card::Eight, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // Two Pair
  std::vector<Card> TwoPair = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Four, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(TwoPair, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
};

TEST(evaluateHandComparison, ThreeOfAKind_vs_TwoPair)
{

  // ThreeOfAKind
  std::vector<Card> ThreeOfAKind = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // Two Pair
  std::vector<Card> TwoPair = {
    Card(Card::Four, Card::Spade),
    Card(Card::Six, Card::Diamond),
    Card(Card::Six, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Ace, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Four, Card::Diamond),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(TwoPair, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Straight_vs_Pair)
{

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Spade),
    Card(Card::Eight, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // Pair
  std::vector<Card> Pair = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Two, Card::Heart),

  };

  std::vector<Card> dealerCards = {
    Card(Card::Ace, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Diamond),
    Card(Card::Jack, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(Pair, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Straight_vs_HighCard)
{

  // Straight 1
  std::vector<Card> Straight1 = {
    Card(Card::Nine, Card::Spade),
    Card(Card::Eight, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // High Card
  std::vector<Card> HighCard = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Two, Card::Heart),

  };

  std::vector<Card> dealerCards = {
    Card(Card::Four, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Diamond),
    Card(Card::Jack, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(Straight1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, ThreeOfAKind_vs_Pair)
{

  // ThreeOfAKind
  std::vector<Card> ThreeOfAKind = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // Pair
  std::vector<Card> Pair = {
    Card(Card::Four, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Four, Card::Diamond),
    Card(Card::Ten, Card::Club),
    Card(Card::Jack, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind, dealerCards);
  long long losingHandResult = handEvaluator.evaluateHand(Pair, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, ThreeOfAKind_vs_HighCard)
{

  // ThreeOfAKind
  std::vector<Card> ThreeOfAKind = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // Pair
  std::vector<Card> HighCard = {
    Card(Card::Eight, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Diamond),
    Card(Card::Ten, Card::Club),
    Card(Card::Jack, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, TwoPair_vs_HighCard)
{

  // TwoPair
  std::vector<Card> TwoPair = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Six, Card::Diamond),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // Pair
  std::vector<Card> HighCard = {
    Card(Card::Eight, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Diamond),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(TwoPair, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Pair_vs_HighCard1)
{

  // Pair
  std::vector<Card> Pair = {
    Card(Card::Seven, Card::Spade),
    Card(Card::Seven, Card::Heart),
    Card(Card::Six, Card::Heart),
    Card(Card::Five, Card::Spade),
  };

  // Pair
  std::vector<Card> HighCard = {
    Card(Card::Eight, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Two, Card::Heart),
    Card(Card::King, Card::Heart),
    Card(Card::Nine, Card::Diamond),
    Card(Card::Ten, Card::Club),
    Card(Card::Three, Card::Club),
  };

  long long winningHandResult = handEvaluator.evaluateHand(Pair, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

// Two Pair
TEST(evaluateHandComparison, ThreeOfAKind_vs_TwoPair_2)
{
  // Three of a kind 1
  std::vector<Card> ThreeOfAKind1 = {
    Card(Card::Seven, Card::Club),
    Card(Card::Seven, Card::Diamond),
    Card(Card::Seven, Card::Spade),
    Card(Card::Two, Card::Diamond),
    Card(Card::Nine, Card::Club),
  };
  // Two Pair 1
  std::vector<Card> TwoPair1 = {
    Card(Card::Nine, Card::Club),
    Card(Card::Nine, Card::Spade),
    Card(Card::Four, Card::Heart),
    Card(Card::Four, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Five, Card::Spade),
  };

  long long winningHandResult =
    handEvaluator.evaluateHand(ThreeOfAKind1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(TwoPair1, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, TwoPair_vs_HighCard_2)
{
  // High Card
  std::vector<Card> HighCard = {
    Card(Card::King, Card::Heart),
  };

  // Pair
  std::vector<Card> TwoPair = {
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
    Card(Card::Four, Card::Diamond),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Spade),
    Card(Card::Jack, Card::Diamond),
    Card(Card::Ten, Card::Heart),
    Card(Card::Five, Card::Diamond)};

  long long winningHandResult =
    handEvaluator.evaluateHand(TwoPair, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

TEST(evaluateHandComparison, Pair_vs_HighCard)
{
  // High Card
  std::vector<Card> HighCard = {
    Card(Card::Seven, Card::Heart),
  };

  // Pair 1
  std::vector<Card> Pair1 = {
    Card(Card::Ace, Card::Diamond),
    Card(Card::Ace, Card::Spade),
  };

  std::vector<Card> dealerCards = {
    Card(Card::Three, Card::Club),
    Card(Card::Four, Card::Spade),
    Card(Card::Jack, Card::Heart),
    Card(Card::Ten, Card::Spade),
    Card(Card::Five, Card::Diamond)};

  long long winningHandResult = handEvaluator.evaluateHand(Pair1, dealerCards);
  long long losingHandResult =
    handEvaluator.evaluateHand(HighCard, dealerCards);

  EXPECT_LT(losingHandResult, winningHandResult);
}

// notes:
/*
- make sure you're in the moon-poker top dir
- have to do `cmake --build build/ -t all` and then `cmake --build build/ -t
test` to run the tests
- you can also do ./build/tests/hand_evaluator_test to just run this one
- './hand_evaluator_test -v' to get more verbose output

*/