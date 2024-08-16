/// \file badugi_evaluator.cpp
/// \date 2023-09-22
/// \author Elijah Widener Ferreira
///
/// \brief Hand evaluation engine for badugi hands.

#include "evaluators/badugi_evaluator.hpp"

#include <algorithm>
#include <cassert>
#include <limits>

long long
BadugiHandEvaluator::evaluateHand(const std::vector<Card>& hand)
{
  int       dugi_level  = evaluateDugiLevel(hand);
  long long lowest_hand = std::numeric_limits<long long>::max();

  // Using a mask to generate valid combinations of cards based on how
  // strong the dugi_level is
  std::vector<bool> mask(hand.size(), false);
  std::fill(mask.end() - dugi_level, mask.end(), true);

  do {
    long long         hand_strength = 0;
    std::vector<Card> temp_combination;
    std::set<int>     unique_ranks;

    // populate combination and set
    for (std::size_t i = 0; i < hand.size(); i++) {
      if (mask[i]) {
        temp_combination.push_back(hand[i]);
        unique_ranks.insert(hand[i].getRank());
      }
    }

    if (validDugi(temp_combination, dugi_level, unique_ranks)) {

      for (const int& rank_value : unique_ranks) {
        // sets are sorted lowest to highest, and use a pointer

        // for aces to be counted as 1, add one to the front of the num
        if (rank_value == 14) {
          hand_strength += pow(10, (dugi_level - 1) * 2);
        } else {
          hand_strength = hand_strength * 100 + rank_value;
        }
      }
      // We are looking for the LOWEST combination
      if (hand_strength < lowest_hand) {
        lowest_hand = hand_strength;
      }
    }
  } while (next_permutation(mask.begin(), mask.end()));

  return lowest_hand;
}

int
BadugiHandEvaluator::evaluateDugiLevel(const std::vector<Card>& hand)
{
  std::set<char> unique_suits;
  std::set<int>  unique_ranksAlpha;

  // Check for unique suits and ranks
  for (const Card& card : hand) {
    unique_suits.insert(card.getSuit());
    unique_ranksAlpha.insert(card.getRank());
  }

  int dugi_level = std::min(unique_ranksAlpha.size(), unique_suits.size());
  return dugi_level;
}

bool
BadugiHandEvaluator::validDugi(
  std::vector<Card> combination,
  int               dugi_level,
  std::set<int>&    unique_ranks)
{
  std::set<char> unique_suits;
  for (const Card& card : combination) {
    unique_suits.insert(card.getSuit());
    unique_ranks.insert(card.getRank());
  }
  int num_suits = std::size(unique_suits);
  int num_ranks = std::size(unique_ranks);
  if ((num_ranks == dugi_level) && (num_suits == dugi_level)) {
    return true;
  } else {
    return false;
  }
}
