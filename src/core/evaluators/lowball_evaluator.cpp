/// \file lowball_evaluator.cpp
/// \date 2023-10-28
/// \author Elijah Widener Ferreira
///
/// \brief Implementation of LowballEvaluator

#include "evaluators/lowball_evaluator.hpp"

long long
LowballEvaluator::evaluateHand(const std::vector<Card>& hand)
{
  std::set<int> unique_ranks;
  long long     hand_strength = 0;
  int           index         = 0;
  int           lowest_five[5];
  int           card_value = 0;

  populateRanks(hand, unique_ranks, false);

  if (unique_ranks.size() < 5) {
    return evaluateLowballNoHighCard(hand);
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
LowballEvaluator::populateRanks(
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
LowballEvaluator::evaluateLowballNoHighCard(const std::vector<Card>& hand)
{
  // Lambda function to calculate hand strength
  auto calculateHandStrength =
    [](std::set<int>& unique_ranks, long long hand_strength, int card_counter) {
      for (int rank_value : unique_ranks) {
        if (card_counter < 5) {
          card_counter++;
          hand_strength = hand_strength * 100 + rank_value;
        }
      }
      return hand_strength;
    };

  std::map<int, int> rank_counts;
  for (const Card& card : hand) {
    int rank = (card.getRank() == 14) ? 1 : card.getRank();
    rank_counts[rank]++;
  }

  std::map<int, int> count_counts;
  for (const auto& [rank, count] : rank_counts) {
    count_counts[count]++;
  }

  // Evaluate One Pair
  if (count_counts[2] >= 1 || (count_counts[3] >= 1)) {

    int pair_rank = 0;
    for (const auto& [rank, count] : rank_counts) {
      if (count == 2 && (rank < pair_rank || pair_rank == 0)) {
        pair_rank = rank;
      }
    }
    // For the very fringe case where trips get played as a pair:
    if (count_counts[3] >= 1) {
      for (const auto& [rank, count] : rank_counts) {
        if (count == 3 && (rank < pair_rank || pair_rank == 0)) {
          pair_rank = rank;
        }
      }
    }

    long long     hand_strength = (200 + pair_rank) * 10;
    std::set<int> unique_ranks;

    populateRanks(hand, unique_ranks, false);
    unique_ranks.erase(pair_rank);
    if (unique_ranks.size() >= 3) {
      return calculateHandStrength(unique_ranks, hand_strength, 2);
    }
  }

  // Evaluate Two Pair
  if (count_counts[2] >= 2) {
    int pair_rank = 0, pair2_rank = 0;
    for (const auto& [rank, count] : rank_counts) {
      if (count == 2 && (rank < pair_rank || pair2_rank == 0)) {
        pair2_rank = pair_rank;
        pair_rank  = rank;
      }
    }
    // pair_rank is the higher pair, pair2_rank is the lower
    long long     hand_strength = ((300 + pair_rank) * 100 + pair2_rank) * 1000;
    std::set<int> unique_ranks;
    populateRanks(hand, unique_ranks, false);
    unique_ranks.erase(pair_rank);
    unique_ranks.erase(pair2_rank);
    if (unique_ranks.size() >= 1) {
      return calculateHandStrength(unique_ranks, hand_strength, 4);
    }
  }

  // Evaluate Trips
  if (count_counts[3] >= 1) {
    int trips_rank = 0;
    for (const auto& [rank, count] : rank_counts) {
      if (count == 3 && ((rank < trips_rank) || trips_rank == 0)) {
        trips_rank = rank;
      }
    }
    std::set<int> unique_ranks;
    long long     hand_strength = (400 + trips_rank) * 1000;

    populateRanks(hand, unique_ranks, false);
    unique_ranks.erase(trips_rank);
    if (unique_ranks.size() >= 2) {
      return calculateHandStrength(unique_ranks, hand_strength, 3);
    }
  }

  // Evaluate Quads(in practice this should never happen)
  if (count_counts[4] >= 1) {
    int quads_rank = 0;
    for (const auto& [rank, count] : rank_counts) {
      if (count == 4 && ((rank < quads_rank) || quads_rank == 0)) {
        quads_rank = rank;
      }
    }
    std::set<int> unique_ranks;
    long long     hand_strength = (500 + quads_rank) * 100000;
    populateRanks(hand, unique_ranks, false);
    unique_ranks.erase(quads_rank);
    if (unique_ranks.size() >= 1) {
      return calculateHandStrength(unique_ranks, hand_strength, 4);
    }
  }
  return -1;
}
