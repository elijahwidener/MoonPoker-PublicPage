/// \file eight_or_better_evaluator.hpp
/// \date 2023-10-28
/// \author Elijah Widener Ferreira
///
/// \brief Hand evaluation engine for "eight or better".

#pragma once

#ifndef __cplusplus
#error "eight_or_better_evaluator.hpp is a cxx-only header."
#endif // __cplusplus

#include <MoonPoker/evaluators/hand_evaluator.hpp>

/// \brief Evaluates hands for lowball games with 'eight or better' to qualify.
///
/// \details some lowball poker games, players must have a hand that is
/// 'eight-high' or better to qualify. This means that all cards being played
/// must be under eight, with aces counting as low. This class inherits from
/// HandEvaluator and implements the necessary logic to evaluate such hands.
class EightOrBetterEvaluator : public HandEvaluator
{
 public:
  /// \brief Evaluates a hand for 'eight or better' lowball games.
  ///
  /// \details Computes the strength of a qualifying low hand in 'eight or
  /// better' format. If the hand does not qualify (not enough ranks 8 or
  /// below), it returns -1.
  /// \param hand Vector of Card objects representing the player's hand.
  /// \return The hand strength as a long long value, or -1 if not qualifying.
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
  /// \param cards Vector of Card objects from which ranks are extracted.
  /// \param ranks The set that will be populated with the unique ranks.
  /// \param eight_or_better Boolean flag indicating whether to apply the
  /// 'eight or better' rule.
  void populateRanks(
    const std::vector<Card>& cards,
    std::set<int>&           ranks,
    bool                     eight_or_better);
};
