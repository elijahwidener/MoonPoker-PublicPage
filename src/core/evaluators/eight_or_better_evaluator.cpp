/// \file eight_or_better_evaluator.cpp
/// \date 2023-10-28
/// \author Elijah Widener Ferreira
///
/// \brief Implementation of EightOrBetterEvaluator

#include "evaluators/eight_or_better_evaluator.hpp"

long long
EightOrBetterEvaluator::evaluateHand(const std::vector<Card>& hand)
{
  std::set<int> unique_ranks;
  long long     hand_strength = 0;
  int           index         = 0;
  int           lowest_five[5];
  int           card_value = 0;

  populateRanks(hand, unique_ranks, true);
  // If there aren't 5 cards under 8, no qualifying low
  if (unique_ranks.size() < 5) {
    return -1;
  }

  for (int rank_value : unique_ranks) {
    if (index < 5) {
      lowest_five[index] = rank_value;
      index++;
    }
  }
  for (index--; index >= 0; index--) {
    card_value    = lowest_five[index];
    hand_strength = hand_strength * 100 + card_value;
  }
  return hand_strength;
}

void
EightOrBetterEvaluator::populateRanks(
  const std::vector<Card>& cards,
  std::set<int>&           ranks,
  bool                     eight_or_better)
{
  for (const Card& card : cards) {
    int rank = (card.getRank() == 14) ? 1 : card.getRank();
    if (!eight_or_better || (eight_or_better && rank <= 8)) {
      ranks.insert(rank);
    }
  }
}
