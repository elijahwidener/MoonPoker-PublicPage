/// \file omaha_evaluator.hpp
/// \date 2023-10-30
/// \author Elijah Widener Ferreira
///
/// \brief Omaha and evaluation engine Extends the HandEvaluator to
/// provide functionality for evaluating Omaha-style poker hands.

#pragma once

#ifndef __cplusplus
#error "omaha_evaluator.hpp is a cxx-only header."
#endif // __cplusplus

#include <MoonPoker/evaluators/standard_evaluator.hpp>

/// \brief Evaluates the best hand given Omaha rules
///
/// \details In Omaha, it is required for players to use two form their hand,
/// and three from the board.
class OmahaEvaluator : public StandardEvaluator
{
 public:
  /// \brief Evaluates an Omaha poker hand.
  ///
  /// \details This evaluation engine iterates through all possible combinations
  /// of two cards from the player's hand in conjunction with the given board
  /// (community cards) to determine the highest possible hand value that
  /// conforms to the rules of Omaha poker.
  ///
  /// \param hand A vector of Card objects representing the player's hand.
  /// \param board A vector of Card objects representing the community cards.
  /// \return The value of the highest hand achievable using two cards from the
  /// hand and three cards on the board.
  long long evaluateHand(
    const std::vector<Card>& hand,
    const std::vector<Card>& board) override;

  /// \copydoc HandEvaluator::evaluateHand
  using HandEvaluator::evaluateHand;
};
