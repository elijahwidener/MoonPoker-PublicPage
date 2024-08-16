/// \file omaha_eight_evaluator_test.cpp
/// \date 2023-11-09
///
/// \brief This file contains tests for the omaha Eight evaluator.

#include <MoonPoker/evaluators/omaha_eight_evaluator.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// ======================= Global Definitions =========================
OmahaEightEvaluator omahaEightEvaluator;
// ====================== omahaEight Tests =========================

TEST(omahaEight, basic_test)
{
  {
    std::vector<Card> hand = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), 805030201);
  }
}
TEST(omahaEight, basic_test2)
{
  {
    std::vector<Card> hand = {
      Card(Card::King, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), 805030201);
  }
}
TEST(omahaEight, basic_test3)
{
  {
    std::vector<Card> hand = {
      Card(Card::King, Card::Spade),
      Card(Card::Eight, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), 805030201);
  }
}
TEST(omahaEight, straight_test)
{
  {
    std::vector<Card> hand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Four, Card::Club),
      Card(Card::Three, Card::Heart),
      Card(Card::Two, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), 504030201);
  }
}
TEST(omahaEight, flush_test)
{
  {
    std::vector<Card> hand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Eight, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Spade),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Spade),
      Card(Card::Eight, Card::Spade),
      Card(Card::Six, Card::Spade),
      Card(Card::Ace, Card::Spade),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), 605030201);
  }
}
TEST(omahaEight, noLow_test)
{
  {
    std::vector<Card> hand = {
      Card(Card::King, Card::Spade),
      Card(Card::King, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::Two, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), -1);
  }
}
TEST(omahaEight, noLow_test2)
{
  {
    std::vector<Card> hand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Five, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::King, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), -1);
  }
}
TEST(omahaEight, noLow_test3)
{
  {
    std::vector<Card> hand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Two, Card::Club),
      Card(Card::Five, Card::Heart),
      Card(Card::Eight, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Eight, Card::Club),
      Card(Card::Nine, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), -1);
  }
}
TEST(omahaEight, noLow_test4)
{
  {
    std::vector<Card> hand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Two, Card::Club),
      Card(Card::Five, Card::Heart),
      Card(Card::Eight, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::King, Card::Spade),
      Card(Card::Queen, Card::Club),
      Card(Card::Jack, Card::Heart),
      Card(Card::Nine, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(hand, board), -1);
  }
}
TEST(omahaEight, comparison_Test)
{
  {
    std::vector<Card> losingHand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Two, Card::Club),
      Card(Card::Five, Card::Heart),
      Card(Card::Eight, Card::Diamond),
    };

    std::vector<Card> winningHand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Two, Card::Club),
      Card(Card::Three, Card::Heart),
      Card(Card::Four, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Eight, Card::Club),
      Card(Card::Nine, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEightEvaluator.evaluateHand(losingHand, board), -1);
    EXPECT_EQ(omahaEightEvaluator.evaluateHand(winningHand, board), 504030201);
  }
}
TEST(omahaEight, comparison_Test2)
{
  {
    std::vector<Card> losingHand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Two, Card::Club),
      Card(Card::Four, Card::Heart),
      Card(Card::Eight, Card::Diamond),
    };

    std::vector<Card> winHand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Two, Card::Club),
      Card(Card::Three, Card::Heart),
      Card(Card::Four, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Eight, Card::Club),
      Card(Card::Nine, Card::Heart),
      Card(Card::Seven, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    long long losing  = omahaEightEvaluator.evaluateHand(losingHand, board);
    long long winning = omahaEightEvaluator.evaluateHand(winHand, board);
    EXPECT_EQ(losing, 807040201);
    EXPECT_EQ(winning, 704030201);
    EXPECT_LT(winning, losing);
  }
}
TEST(omahaEight, comparison_Test3)
{
  {
    std::vector<Card> losingHand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Four, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::Ten, Card::Diamond),
    };

    std::vector<Card> winHand = {
      Card(Card::Two, Card::Spade),
      Card(Card::King, Card::Club),
      Card(Card::Three, Card::Heart),
      Card(Card::Ten, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::King, Card::Spade),
      Card(Card::Six, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::Seven, Card::Diamond),
      Card(Card::Eight, Card::Diamond),
    };

    long long losing  = omahaEightEvaluator.evaluateHand(losingHand, board);
    long long winning = omahaEightEvaluator.evaluateHand(winHand, board);
    EXPECT_EQ(losing, 807060401);
    EXPECT_EQ(winning, 807060302);
    EXPECT_LT(winning, losing);
  }
}
TEST(omahaEight, comparison_Test4)
{
  {
    std::vector<Card> losingHand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Four, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::Ten, Card::Diamond),
    };

    std::vector<Card> winHand = {
      Card(Card::Two, Card::Spade),
      Card(Card::King, Card::Club),
      Card(Card::Three, Card::Heart),
      Card(Card::Ten, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Four, Card::Club),
      Card(Card::Three, Card::Heart),
      Card(Card::Two, Card::Diamond),
      Card(Card::Eight, Card::Diamond),
    };

    long long losing  = omahaEightEvaluator.evaluateHand(losingHand, board);
    long long winning = omahaEightEvaluator.evaluateHand(winHand, board);
    EXPECT_EQ(losing, 804030201);
    EXPECT_EQ(winning, 804030201);
    EXPECT_EQ(winning, losing);
  }
}
TEST(omahaEight, comparison_Test5)
{
  {
    std::vector<Card> losingHand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Eight, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::Ten, Card::Diamond),
    };

    std::vector<Card> winHand = {
      Card(Card::Two, Card::Spade),
      Card(Card::King, Card::Club),
      Card(Card::Three, Card::Heart),
      Card(Card::Ten, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Nine, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::King, Card::Diamond),
      Card(Card::Eight, Card::Diamond),
    };

    long long losing  = omahaEightEvaluator.evaluateHand(losingHand, board);
    long long winning = omahaEightEvaluator.evaluateHand(winHand, board);
    EXPECT_EQ(losing, -1);
    EXPECT_EQ(winning, -1);
    EXPECT_EQ(winning, losing);
  }
}
