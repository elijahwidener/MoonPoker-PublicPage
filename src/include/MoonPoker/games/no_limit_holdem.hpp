/// \file no_limit_holdem.cpp
/// \date 2023-12-20
/// \author Elijah Widener Ferreira
///
/// \brief Concrete header file of the No Limit Hold'em game.

#pragma once

#include "MoonPoker/evaluators/standard_evaluator.hpp"
#include "MoonPoker/games/community_card_structure.hpp"

/// \brief Two hole cards and five community cards.
///
/// \details No limit holdem is the most popular poker game played. It is played
/// with two hole cards and five community cards. The player with the best five
/// card hand under the basic hand rankings wins the pot. The game is played No
/// Limit.
class NoLimitHoldem : public CommunityCard
{
 public:
  /// \brief Constructor for NoLimitHoldem.
  /// \param ante The ante amount for the game.
  /// \param small_blind The small blind amount for the game.
  /// \param big_blind The big blind amount for the game.
  NoLimitHoldem(int ante, int small_blind, int big_blind);

  /// \brief Overrides the playHand method for No Limit Hold'em.
  /// \details Specific to No Limit Hold'em game logic, including handling
  /// blinds, dealing hole cards, and managing betting rounds.
  /// Inherits basic behavior from the Game class.
  void playHand() override;
};
