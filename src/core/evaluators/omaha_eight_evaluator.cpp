/// \file omaha_eight_evaluator.cpp
/// \date 2023-11-02
/// \author Elijah Widener Ferreira
///
/// \brief Implementation of the OmahaEightEvaluator

#include "evaluators/omaha_eight_evaluator.hpp"

#include <cassert>
#include <cstdint>
#include <limits>

long long
OmahaEightEvaluator::evaluateHand(
  const std::vector<Card>& hand,
  const std::vector<Card>& board)
{
  std::set<int> unique_ranks;
  std::set<int> unique_ranks_board;
  long long     lowest_hand = std::numeric_limits<long long>::max();

  // Isolate cards under 8
  populateRanks(board, unique_ranks_board, true);
  // If there are not 3 cards on the board under 3, no one can make a low
  if (unique_ranks_board.size() < 3) {
    return -1;
  }

  populateRanks(hand, unique_ranks, true);
  // If there are not 2 cards under 8, hand cannot qualify for a low
  if (unique_ranks.size() < 2) {
    return -1;
  };

  std::vector<bool> mask(unique_ranks.size(), false);
  std::fill(mask.end() - 2, mask.end(), true);

  do {
    std::set<int, std::greater<int>> temp_combination;
    int                              i             = 0;
    long long                        hand_strength = 0;

    // Fill the combination with cards from hand
    for (int rank : unique_ranks) {
      if (mask[i]) {
        temp_combination.insert(rank);
      }
      i++;
    }

    // Fill tempCombination with the lowest card from the board.
    // Since sets do not include duplicates, we can keep adding
    // the lowest until the size reaches 5, or we run out of cards to add.
    // Keep in mind that uniqueRanksBoard sets are sorted in least -> greatest,
    // while tempCombination is sorted greatest -> least
    for (int rank : unique_ranks_board) {
      if (temp_combination.size() != 5) {
        temp_combination.insert(rank);
      }
    }

    // If the size of tempCombination is not 5, we
    // did not have enough unique cards under 8, and cannot
    // make a low
    if (temp_combination.size() == 5) {
      for (int rank_value : temp_combination) {
        hand_strength = hand_strength * 100 + rank_value;
      }
      if (hand_strength < lowest_hand) {
        lowest_hand = hand_strength;
      }
    }

  } while (next_permutation(mask.begin(), mask.end()));

  // No low
  if (lowest_hand == std::numeric_limits<long long>::max()) {
    return -1;
  }

  return lowest_hand;
}

void
OmahaEightEvaluator::populateRanks(
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

long long
OmahaEightEvaluator::evaluateHand(const std::vector<Card>& hand)
{
  static_cast<void>(hand);
  assert(false && "This function should never be called.");
  return -1;
}
