/// \file omaha_eight_evaluator.hpp
/// \date 2023-11-02
/// \author Elijah Widener Ferreira
///
/// \brief Omaha Hi-Lo (Eight or Better) hand evaluation.

#pragma once

#ifndef __cplusplus
#error "omaha_eight_evaluator.hpp is a cxx-only header."
#endif // __cplusplus

#include <MoonPoker/evaluators/hand_evaluator.hpp>

/// \brief Evaluator for Omaha Hi-Lo (Eight or Better) hands.
///
/// \details In Omaha, it is required for players to use two form their hand,
/// and three from the board. Omaha lo always is played with the eight or better
/// requirement for lo hands
class OmahaEightEvaluator : public HandEvaluator
{
 public:
  /// \brief Evaluate an Omaha Hi-Lo hand.
  ///
  /// \details Considers both the player's hand and the community cards to
  /// determine the best possible low hand that qualifies. Qualifying
  /// hands must have 5 unique cards under 8.
  ///
  /// \param hand Player's hand.
  /// \param board Community cards.
  /// \return Strength of the lowest qualifying hand or -1 if no low hand is possible.
  long long evaluateHand(
    const std::vector<Card>& hand,
    const std::vector<Card>& board) override;

  /// \copydoc HandEvaluator::evaluateHand
  using HandEvaluator::evaluateHand;

 private:
  /// \brief Populates a set with unique ranks, allows for 'eight or better'.
  ///
  /// \details This helper function fills a set with unique ranks from a vector
  /// of cards. If 'eightOrBetter' is true, it only includes cards with a rank
  /// of 8 or below.
  ///
  /// \param cards Vector of Card objects from which ranks are extracted.
  /// \param ranks The set that will be populated with the unique ranks.
  /// \param eightOrBetter Boolean flag indicating whether to apply the 'eight
  /// or better' rule.
  void populateRanks(
    const std::vector<Card>& cards,
    std::set<int>&           ranks,
    bool                     eightOrBetter);

  long long evaluateHand(const std::vector<Card>& hand) override;
};
