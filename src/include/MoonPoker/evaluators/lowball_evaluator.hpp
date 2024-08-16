/// \file lowball_evaluator.hpp
/// \date 2023-10-28
/// \author Elijah Widener Ferreira
///
/// \brief Hand evaluation engine for classic Lowball.

#pragma once

#ifndef __cplusplus
#error "lowball_evaluator.hpp is a cxx-only header."
#endif // __cplusplus

#include <MoonPoker/evaluators/hand_evaluator.hpp>

/// \brief Evaluates hands for classic lowball games.
///
/// In classic lowball games, the aim is to have the lowest hand possible.
/// Straight and flushes do not count against the player.
class LowballEvaluator : public HandEvaluator
{
 public:
  /// \brief Evaluates a Lowball poker hand.
  ///
  /// \details The evaluation is based on the lowest 5 unique cards in the hand.
  /// Straights and flushes are not considered in the evaluation.
  /// If a 5-card hand cannot be formed, the worst possible traditional poker
  /// hand is used.
  ///
  /// \param hand Vector of Card objects representing the player's hand.
  /// \return A long long representing the hand's strength; -1 if a Lowball hand cannot be made.
  long long evaluateHand(const std::vector<Card>& hand) override;

  /// \copydoc HandEvaluator::evaluateHand
  using HandEvaluator::evaluateHand;

 private:
  /// \brief Populates a set with unique ranks, allows for 'eight or
  /// better'.
  ///
  /// \details This helper function fills a set with unique ranks from a vector
  /// of cards. If 'eightOrBetter' is true, it only includes cards with a rank
  /// of 8 or below.
  ///
  /// \param cards Vector of Card objects from which ranks are extracted.
  /// \param ranks The set that will be populated with the unique ranks.
  /// \param eight_or_better Boolean flag indicating whether to apply the
  /// 'eight or better' rule.
  void populateRanks(
    const std::vector<Card>& cards,
    std::set<int>&           ranks,
    bool                     eight_or_better);

  /// \brief Evaluates the worst Lowball hand if no qualifying high card hand
  /// can be made.
  ///
  /// \details This method evaluates the hand based on traditional poker
  /// rankings, to determine the weakest possible hand if no low hand can be
  /// made.
  ///
  /// \param hand A vector of Card objects representing the player's hand.
  /// \return A long long representing the hand's strength in traditional poker ranking.
  long long evaluateLowballNoHighCard(const std::vector<Card>& hand);
};
