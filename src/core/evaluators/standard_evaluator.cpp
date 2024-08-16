/// \file standard_evaluator.cpp
/// \date 2023-11-02
/// \author Elijah Widener Ferreira
///
/// \brief Implementation of the StandardEvaluator.

#include "evaluators/standard_evaluator.hpp"

#include <algorithm>

long long
StandardEvaluator::evaluateHand(
  const std::vector<Card>& hand,
  const std::vector<Card>& board)
{
  // Combine player's cards with community cards
  std::vector<Card> hand_plus_board = hand;
  hand_plus_board.insert(hand_plus_board.end(), board.begin(), board.end());

  return evaluateHand(hand_plus_board);
}

long long
StandardEvaluator::evaluateHand(const std::vector<Card>& hand)
{
  auto&& hand_plus_board = hand;

  // Count occurrences of each rank
  std::map<int, int> rank_counts;
  for (const Card& card : hand_plus_board) {
    rank_counts[card.getRank()]++;
  }
  // The key will be integer rank values (2-14) for 2-A
  // The value will be the amount of times it appears

  // Count occurrences of each count (to identify pairs, trips, etc.)
  std::map<int, int> count_counts;
  for (const auto& [rank, count] : rank_counts) {
    count_counts[count]++;
  }

  // Prepare a sorted list of unique ranks for checking straights
  std::vector<int> unique_ranks;
  for (const auto& [rank, count] : rank_counts) {
    unique_ranks.push_back(rank);
  }
  sort(unique_ranks.begin(), unique_ranks.end());
  int straight_strength = isStraight(unique_ranks);

  // Evaluation:
  if ((straight_strength != 0) && isFlush(hand_plus_board)) {

    std::map<char, std::vector<int>> suit_ranks;

    for (const Card& card : hand_plus_board) {
      suit_ranks[card.getSuit()].push_back(card.getRank());
    }

    for (auto& [suit, ranks] : suit_ranks) {
      if (ranks.size() >= 5) {
        sort(ranks.begin(), ranks.end());
        int consecutive_count       = 1;
        int straight_flush_strength = 0;

        for (std::size_t i = 1; i < ranks.size(); ++i) {
          if (ranks[i] == ranks[i - 1] + 1) {
            consecutive_count++;
            if (consecutive_count >= 5) {
              straight_flush_strength = ranks[i];
            }
          } else {
            consecutive_count = 1;
          }
        }
        if (straight_flush_strength != 0)
          return kStraightFlush +
            straight_flush_strength; // This is a straight flush

        // Check for steel wheel
        if (
          find(ranks.begin(), ranks.end(), 14) != ranks.end() &&
          find(ranks.begin(), ranks.end(), 2) != ranks.end() &&
          find(ranks.begin(), ranks.end(), 3) != ranks.end() &&
          find(ranks.begin(), ranks.end(), 4) != ranks.end() &&
          find(ranks.begin(), ranks.end(), 5) != ranks.end()) {
          straight_flush_strength = 5;
        }

        if (straight_flush_strength != 0)
          return kStraightFlush + straight_flush_strength;
      }
    }
  }

  // Four of a kind
  if (count_counts[4] == 1) {
    int quads_rank = 0;
    for (const auto& [rank, count] : rank_counts) {
      if (count == 4) {
        quads_rank = rank;
        unique_ranks.erase(
          find(unique_ranks.begin(), unique_ranks.end(), quads_rank));
        break;
      }
    }
    return kFourOfAKind + (quads_rank * 100) + unique_ranks.back();
  }

  // Full house
  if (
    (count_counts[3] == 1 && count_counts[2] >= 1) || (count_counts[3] == 2)) {
    int trips_rank[2] = {0, 0};
    int pairs[2]      = {0, 0};
    for (const auto& [rank, count] : rank_counts) {
      if (count == 3) {
        if (rank > trips_rank[0]) {
          trips_rank[1] = trips_rank[0];
          trips_rank[0] = rank;
        }
      }
      if (count == 2) {
        if (rank > pairs[0]) {
          pairs[1] = pairs[0];
          pairs[0] = rank;
        }
      }
    }
    if (trips_rank[1] != 0) {
      return kFullHouse + (trips_rank[0] * 100) + trips_rank[1];
    }

    return kFullHouse + (trips_rank[0] * 100) + pairs[0];
  }

  // Flush
  if (isFlush(hand_plus_board)) {
    long long kicker_value = 0;
    kicker_value           = kickers(unique_ranks, 5);
    return kFlush + kicker_value;
  }

  // Straight
  if (straight_strength != 0)
    return kStraight + straight_strength;

  // Three of a Kind
  if (count_counts[3] == 1) {
    int trips_rank = 0;
    for (const auto& [rank, count] : rank_counts) {
      if (count == 3) {
        trips_rank = rank;
        unique_ranks.erase(
          find(unique_ranks.begin(), unique_ranks.end(), trips_rank));
        break;
      }
    }
    long long kicker_value = 0;
    kicker_value           = kickers(unique_ranks, 2);
    return kThreeOfAKind + (trips_rank * 10000) + kicker_value;
  }

  // Two Pair
  if (count_counts[2] >= 2) {
    int pairs[3] = {0, 0, 0};

    for (const auto& [rank, count] : rank_counts) {
      if (count == 2) {
        if (rank > pairs[0]) {
          pairs[2] = pairs[1];
          pairs[1] = pairs[0];
          pairs[0] = rank;
        } else if (rank > pairs[1]) {
          pairs[2] = pairs[1];
          pairs[1] = rank;
        } else if (rank > pairs[2]) {
          pairs[2] = rank;
        }
      }
    }
    unique_ranks.erase(
      find(unique_ranks.begin(), unique_ranks.end(), pairs[0]));
    unique_ranks.erase(
      find(unique_ranks.begin(), unique_ranks.end(), pairs[1]));
    return kTwoPair + (pairs[0] * 10000) + (pairs[1] * 100) +
      unique_ranks.back();
  }

  // One Pair
  if (count_counts[2] == 1) {
    int pair_rank = 0;
    for (const auto& [rank, count] : rank_counts) {
      if (count == 2) {
        pair_rank = rank;
        unique_ranks.erase(
          find(unique_ranks.begin(), unique_ranks.end(), pair_rank));
        break;
      }
    }
    long long kicker_value = 0;
    kicker_value           = kickers(unique_ranks, 3);
    return kOnePair + pair_rank * 100000000 + kicker_value;
  }

  // High card
  return kickers(unique_ranks, 5);
}

long long
StandardEvaluator::kickers(std::vector<int>& unique_ranks, int num_kickers)
{

  // Sort the vector in descending order
  sort(unique_ranks.begin(), unique_ranks.end(), std::greater<int>());

  int kicker_value = 0;

  // Take the required number of elements and construct the number
  for (int i = 0; i < num_kickers; i++) {
    kicker_value = kicker_value * 100 + unique_ranks[i];
  }

  return kicker_value;
}

int
StandardEvaluator::isStraight(const std::vector<int>& unique_ranks)
{
  int consecutive_count = 1;
  int straight_strength = 0;

  for (std::size_t i = 1; i < unique_ranks.size(); ++i) {
    if (unique_ranks[i] == unique_ranks[i - 1] + 1) {
      consecutive_count++;
      if (consecutive_count >= 5) {
        straight_strength = unique_ranks[i];
      }

    } else {
      consecutive_count = 1;
    }
  }
  if (straight_strength != 0) {
    return straight_strength;
  } // Check for a wheel (A-2-3-4-5)
  if (
    find(unique_ranks.begin(), unique_ranks.end(), 14) != unique_ranks.end() &&
    find(unique_ranks.begin(), unique_ranks.end(), 2) != unique_ranks.end() &&
    find(unique_ranks.begin(), unique_ranks.end(), 3) != unique_ranks.end() &&
    find(unique_ranks.begin(), unique_ranks.end(), 4) != unique_ranks.end() &&
    find(unique_ranks.begin(), unique_ranks.end(), 5) != unique_ranks.end()) {
    return 5; // Return the strength of a wheel
  }
  return straight_strength;
}

bool
StandardEvaluator::isFlush(const std::vector<Card>& hand_plus_board)
{
  std::map<Card::Suit, int> suit_counts;
  for (const Card& card : hand_plus_board) {
    suit_counts[card.getSuit()]++;
  }
  for (const auto& [suit, count] : suit_counts) {
    if (count >= 5)
      return true;
  }
  return false;
}
