/// \file omaha_evaluator.cpp
/// \date 2023-10-30
/// \author Elijah Widener Ferreira
///
/// \brief Implementation of OmahaEvaluator.

#include "evaluators/omaha_evaluator.hpp"

long long
OmahaEvaluator::evaluateHand(
  const std::vector<Card>& hand,
  const std::vector<Card>& board)
{
  long long highest_hand = 0;

  // Omaha requires the player to use two cards from their hand,
  // so we will create a mask size 4 with 2 entry spaces for the hand.
  std::vector<bool> hand_mask(4, false);
  std::fill(hand_mask.end() - 2, hand_mask.end(), true);

  // Then, we will create a mask size 5 with 3 entry spaces for the board.
  // Together, these ensure the algorithm is following omaha rules.
  std::vector<bool> board_mask(5, false);
  std::fill(board_mask.end() - 3, board_mask.end(), true);

  do {
    std::vector<Card> hand_combination;

    // Fill the combination with 2 cards based on the mask
    for (int i = 0; i < 4; i++) {
      if (hand_mask[i]) {
        hand_combination.push_back(hand[i]);
      }
    }
    do {
      std::vector<Card> board_combination;

      // Fill the combination with 3 cards based on the mask
      for (int k = 0; k < 5; k++) {
        if (board_mask[k]) {
          board_combination.push_back(board[k]);
        }
      }

      // Evaluate the hand_strength and compare to previous combination
      long long hand_strength =
        StandardEvaluator::evaluateHand(hand_combination, board_combination);
      if (hand_strength > highest_hand) {
        highest_hand = hand_strength;
      }
    } while (next_permutation(
      board_mask.begin(), board_mask.end())); // 10 permutations

  } while (
    next_permutation(hand_mask.begin(), hand_mask.end())); // 6 permutations

  return highest_hand;
}
