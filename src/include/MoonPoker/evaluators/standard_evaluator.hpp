/// \file standard_evaluator.hpp
/// \date 2023-11-02
/// \author Elijah Widener Ferreira
///
/// \brief Evaluation engine for  the strength of a poker hand using
/// a standard set of poker rules.

#pragma once

#ifndef __cplusplus
#error "standard_evaluator.hpp is a cxx-only header."
#endif // __cplusplus

#include <map>
#include <vector>

#include "MoonPoker/evaluators/hand_evaluator.hpp"

/// \brief Evaluates poker hands according to standard poker rules.
///
/// \details Inherits from HandEvaluator and implements the evaluation logic for
/// different poker hand types like flush, straight, full house, etc.
class StandardEvaluator : public HandEvaluator
{
 public:
  /// \brief Evaluates a poker hand with the board to determine the strength.
  ///
  /// \details Standard rankings have 9 categories, see in \ref HandStrength.
  /// Each category can then be ranked further, based on the strength of the
  /// pair, flush, straight, etc. and finally can be ranked again based on the
  /// kickers (highest remaining cards).
  ///
  /// \param hand A vector of Cards representing the player's hand.
  /// \param board A vector of Cards representing the community cards (board).
  /// \return A long long value representing the hand's strength according to
  /// the HandStrength enum.
  long long evaluateHand(
    const std::vector<Card>& hand,
    const std::vector<Card>& board) override;

  /// \copydoc HandEvaluator::evaluateHand
  long long evaluateHand(const std::vector<Card>& hand) override;

  /// \brief Enum for hand strength magic numbers.
  enum HandStrength : long long
  {
    kOnePair       = 20000000000,
    kTwoPair       = 30000000000,
    kThreeOfAKind  = 40000000000,
    kStraight      = 50000000000,
    kFlush         = 60000000000,
    kFullHouse     = 70000000000,
    kFourOfAKind   = 80000000000,
    kStraightFlush = 90000000000
  };

  /// \brief Computes the kicker value from a set of unique card ranks.
  ///
  /// The function expects the unique ranks to be sorted in descending order.
  /// It then constructs a numeric representation of the kickers based on the
  /// required number.
  ///
  /// \param unique_ranks A vector of integers representing unique card ranks.
  /// \param num_kickers The number of kickers to evaluate from the
  /// uniqueRanks vector.
  /// \return A long long representing the combined kicker value.
  long long kickers(std::vector<int>& unique_ranks, int num_kickers);

  /// \brief Checks if a straight exists within a set of unique card ranks.
  ///
  /// The function checks for a sequence of 5 consecutive card ranks to
  /// identify a straight. It also accounts for the special case of a 'wheel'
  /// (A-2-3-4-5).
  ///
  /// \param unique_ranks A sorted vector of integers representing unique card
  /// ranks.
  /// \return An integer representing the highest rank in the straight, or 0
  /// if no straight is found.
  int isStraight(const std::vector<int>& unique_ranks);

  ///\brief Checks for a flush in a combined set of hand and board cards.
  ///
  /// The function counts the occurrences of each suit and determines if there
  /// are at least 5 of any suit.
  ///
  ///\param hand_plus_board A vector of Card objects representing a player's
  /// hand combined with the community cards.
  ///\return A boolean value: true if a flush is found, false otherwise.
  bool isFlush(const std::vector<Card>& hand_plus_board);
};
