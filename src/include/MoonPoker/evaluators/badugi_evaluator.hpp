/// \file badugi_evaluator.hpp
/// \date 2023-10-28
/// \author Elijah Widener Ferreira
///
/// \brief Hand evaluation engine for badugi hands.

#pragma once

#ifndef __cplusplus
#error "badugi_evaluator.hpp is a cxx-only header."
#endif // __cplusplus

#include <cmath>

#include <MoonPoker/evaluators/hand_evaluator.hpp>

/// \brief Evaluates the best Badugi hand from a given set of cards.
///
/// \details A Badugi hand is unique to the game of Badugi. It consists of four
/// cards with the lowest hand winning, avoiding any pairs and cards with
/// matching suits.
class BadugiHandEvaluator : public HandEvaluator
{
 public:
  /// \brief Calculates the strength of a Badugi hand.
  ///
  /// \param hand Vector of Card objects representing the player's hand.
  /// \return The Badugi rank represented by a long long value.
  long long evaluateHand(const std::vector<Card>& hand) override;

  /// \copydoc HandEvaluator::evaluateHand
  using HandEvaluator::evaluateHand;

  /// \brief Evaluates the level of 'dugi' for a given hand
  ///
  /// \details The 'dugi level' is determined by the number of unique suits and
  /// ranks present in the hand. 4 unique suits and ranks is a 4-dugi, while 3
  /// is a 3-dugi, and so on.
  /// \param hand Vector of Card objects representing the player's hand.
  /// \return The 'dugi level' of the hand as an integer.

  int evaluateDugiLevel(const std::vector<Card>& hand);

  /// \brief Determines if a given combination of cards forms a valid Badugi
  /// hand given the dugi level.
  ///
  /// \details A valid Badugi hand must have the same number of unique suits and
  /// ranks as the 'dugi level', which means no duplicate suits or ranks.
  /// \param combination A vector of cards representing a potential hand.
  /// \param dugi_level The number of unique suits/ranks the hand will be comprised of.
  /// \param unique_ranks A set of ints for the unique ranks.
  /// \return True if the combination is a valid Badugi hand, false otherwise.

  bool validDugi(
    std::vector<Card> combination,
    int               dugi_level,
    std::set<int>&    unique_ranks);
};
