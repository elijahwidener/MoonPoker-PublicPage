/// \file hand_evaluator.hpp
/// \date 2023-10-28
/// \author Elijah Widener Ferreira
///
/// \brief Abstract class for hand evaluation engines.

#pragma once

#ifndef __cplusplus
#error "hand_evaluator.hpp is a cxx-only header."
#endif // __cplusplus

#include <map>
#include <set>

#include "MoonPoker/deck.hpp"

/// \brief Abstract class for hand evaluation engines.
class HandEvaluator
{
 public:
  /// \brief Virtual destructor.
  virtual ~HandEvaluator() = default;

  /// \brief Evaluate the given poker hand and return its rank.
  ///
  /// \details Pure virtual function that must be implemented by derived classes
  /// to assess the strength of a hand according to the rules of the specific
  /// variant of poker being played.
  ///
  /// \param hand Vector of Card objects representing the player's hand.
  /// \return A long long that represents the strength of the hand.
  virtual long long evaluateHand(const std::vector<Card>& hand) = 0;

  /// \brief Evaluate the combined strength of the player's hand and the board.
  ///
  /// \details This is a virtual function that must be overriden by derived
  /// classes to determine the value or rank of a poker hand in relation to the
  /// board. It calculates the strength of the hand by considering both the
  /// individual hand and the cards on the board to determine the best possible
  /// combination. This is important for games like omaha where there is a
  /// distinction between player cards and board cards.
  ///
  /// \param hand A vector of Card objects representing the player's hand.
  /// \param board A vector of Card objects representing the community cards.
  ///
  /// \return A long long value representing the strength of the hand when
  /// combined with the board.
  virtual long long evaluateHand(
    const std::vector<Card>& hand,
    const std::vector<Card>& board)
  {
    static_cast<void>(board);
    return evaluateHand(hand);
  };
};
