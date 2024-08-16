/// \file omaha_evaluator.cpp
/// \date 2023-11-10
///
/// \author Elijah Widener Ferreira
/// \brief This file contains tests for the omaha evaluator.

#include <MoonPoker/evaluators/omaha_evaluator.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// ======================= Global Definitions =========================
OmahaEvaluator omahaEvaluator;
// ====================== omaha Tests =========================
TEST(omaha, high_card_test)
{
  {
    std::vector<Card> hand = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Jack, Card::Heart),
      Card(Card::King, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Queen, Card::Spade),
      Card(Card::Four, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Six, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 1413121108);
  }
}
TEST(omaha, high_card_test2)
{
  {
    std::vector<Card> hand = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Four, Card::Heart),
      Card(Card::Five, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Queen, Card::Spade),
      Card(Card::Jack, Card::Club),
      Card(Card::Ten, Card::Heart),
      Card(Card::King, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 1413120504);
  }
}
TEST(omaha, two_pair_test)
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

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 30000080514);
  }
}
TEST(omaha, two_pair_test2)
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

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 30000080514);
  }
}
TEST(omaha, trips_test)
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

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 40000081405);
  }
}
TEST(omaha, trips_test2)
{
  {
    std::vector<Card> hand = {
      Card(Card::King, Card::Spade),
      Card(Card::Ace, Card::Club),
      Card(Card::Two, Card::Heart),
      Card(Card::Five, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Jack, Card::Spade),
      Card(Card::Jack, Card::Club),
      Card(Card::Jack, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 40000111413);
  }
}
TEST(omaha, straight_wheel_test)
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

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 50000000005);
  }
}
TEST(omaha, straight_test)
{
  {
    std::vector<Card> hand = {
      Card(Card::Ten, Card::Spade),
      Card(Card::King, Card::Club),
      Card(Card::Four, Card::Heart),
      Card(Card::Five, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Club),
      Card(Card::Ace, Card::Heart),
      Card(Card::Queen, Card::Diamond),
      Card(Card::Jack, Card::Diamond),
    };
    // There is a 5 high straight, and an ace high straight, A high wins
    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 50000000014);
  }
}
TEST(omaha, flush_test)
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
      Card(Card::King, Card::Spade),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 61413080605);
  }
}
TEST(omaha, flush_test2)
{
  {
    std::vector<Card> hand = {
      Card(Card::King, Card::Spade),
      Card(Card::Eight, Card::Heart),
      Card(Card::Ace, Card::Heart),
      Card(Card::Five, Card::Spade),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Three, Card::Heart),
      Card(Card::Eight, Card::Heart),
      Card(Card::Six, Card::Spade),
      Card(Card::Queen, Card::Spade),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 61312060502);
  }
}
TEST(omaha, full_house_test)
{
  {
    std::vector<Card> hand = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Ace, Card::Club),
      Card(Card::Two, Card::Heart),
      Card(Card::Two, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Eight, Card::Club),
      Card(Card::Eight, Card::Heart),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 70000001408);
  }
}
TEST(omaha, full_house_test2)
{
  {
    std::vector<Card> hand = {
      Card(Card::Jack, Card::Spade),
      Card(Card::Two, Card::Club),
      Card(Card::Two, Card::Heart),
      Card(Card::Eight, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Ace, Card::Spade),
      Card(Card::Ace, Card::Club),
      Card(Card::Ace, Card::Heart),
      Card(Card::Queen, Card::Diamond),
      Card(Card::Queen, Card::Heart),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 70000001402);
  }
}
TEST(omaha, quads_test)
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
      Card(Card::King, Card::Club),
      Card(Card::King, Card::Spade),
      Card(Card::Five, Card::Diamond),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 80000001314);
  }
}
TEST(omaha, straight_flush_test)
{
  {
    std::vector<Card> hand = {
      Card(Card::King, Card::Club),
      Card(Card::Ace, Card::Club),
      Card(Card::King, Card::Heart),
      Card(Card::Two, Card::Diamond),
    };

    std::vector<Card> board = {
      Card(Card::Two, Card::Spade),
      Card(Card::Jack, Card::Club),
      Card(Card::Queen, Card::Club),
      Card(Card::Ten, Card::Club),
      Card(Card::Ace, Card::Diamond),
    };

    EXPECT_EQ(omahaEvaluator.evaluateHand(hand, board), 90000000014);
  }
}

/**
TEST(omaha, comparison_Test)
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

    EXPECT_EQ(omahaEvaluator.evaluateHand(losingHand, board), -1);
    EXPECT_EQ(omahaEvaluator.evaluateHand(winningHand, board), 504030201);
  }
}
TEST(omaha, comparison_Test2)
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

    long long losing  = omahaEvaluator.evaluateHand(losingHand, board);
    long long winning = omahaEvaluator.evaluateHand(winHand, board);
    EXPECT_EQ(losing, 807040201);
    EXPECT_EQ(winning, 704030201);
    EXPECT_LT(winning, losing);
  }
}
TEST(omaha, comparison_Test3)
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

    long long losing  = omahaEvaluator.evaluateHand(losingHand, board);
    long long winning = omahaEvaluator.evaluateHand(winHand, board);
    EXPECT_EQ(losing, 807060401);
    EXPECT_EQ(winning, 807060302);
    EXPECT_LT(winning, losing);
  }
}
TEST(omaha, comparison_Test4)
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

    long long losing  = omahaEvaluator.evaluateHand(losingHand, board);
    long long winning = omahaEvaluator.evaluateHand(winHand, board);
    EXPECT_EQ(losing, 804030201);
    EXPECT_EQ(winning, 804030201);
    EXPECT_EQ(winning, losing);
  }
}
TEST(omaha, comparison_Test5)
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

    long long losing  = omahaEvaluator.evaluateHand(losingHand, board);
    long long winning = omahaEvaluator.evaluateHand(winHand, board);
    EXPECT_EQ(losing, -1);
    EXPECT_EQ(winning, -1);
    EXPECT_EQ(winning, losing);
  }
}
**/