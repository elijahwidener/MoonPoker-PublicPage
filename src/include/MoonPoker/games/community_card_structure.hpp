/// \file community_card_structure.cpp
/// \date 2023-11-23
/// \author Elijah Widener Ferreira
///
/// \brief Basic structure of community card games.

#pragma once

#ifndef __cplusplus
#error "community_card_structure.hpp is a cxx-only header."
#endif // __cplusplus

#include "MoonPoker/games/abstract_game.hpp"
#include <array>
#include <memory>

/// \brief Represents a game with community cards.
///
/// \details The CommunityCard class refines the Game class and provides
/// functionality for a game with community cards. No new variables are defined,
/// all remaining variables are to be defined in the concrete implementations fo
/// the class.
class CommunityCard : public Game
{
 protected:
  static constexpr int                                       kMaxPlayers = 9;
  std::vector<std::reference_wrapper<PlayerState>>::iterator actions_on_you;
  std::array<Seat, kMaxPlayers>                              seats;

 public:
  CommunityCard(
    int                            ante,
    int                            small_blind,
    int                            big_blind,
    int                            num_cards,
    std::unique_ptr<HandEvaluator> evaluator) :
      Game(ante, small_blind, big_blind, num_cards, std::move(evaluator))
  {
    populatePlayersInHand();
  }

  /// \brief Populates the players_in_hand vector from seats that are filled
  /// with players who are active.
  /// \details This function is called at the beginning of each new hand. The function
  /// works by iterating through the seats array, and if the seat is filled, and
  /// the player active, the player is added to the players_in_hand vector.
  /// \note The seats array gets shifted left after each hand with the \ref CommunityCard::moveButton() function.
  /// This is relevant because players_in_hand, will always start with the
  /// player to the left of the button, and end with the button.
  void populatePlayersInHand();

  /// \brief Shuffles deck, deals cards and posts blinds.
  /// \details Shuffles the mucked cards back into the deck. Then deals
  /// cards based on the num_cards variable. Posts antes for all players if
  /// there is one, and pots big and small blind, as well as updating the
  /// min_bet amount.
  void dealAndPostBlinds();

  /// \brief Deals a single card to the board.
  void dealCardToBoard();

  /// @brief Moves the community cards into the mucked cards pile.
  void muckCommunityCards();

  /// \brief Resets each players betting variables, and sets the actions_on_you
  /// to left of button.
  void resetStreet();

  /// \brief Play a single street of the hand.
  /// \details This function is called for each street of the hand, and loops
  /// through players until action is closed as defined in \ref
  /// Game::closeAction().
  void bettingStreet();

  /// \brief Ends the round and awards the pots to the winning hands.
  ///
  /// \details When a player can't match the bet of another player, the can
  /// still call and go all in, creating a side pot. They are only eligible to
  /// win as much as they put in from each player. This function goes through
  /// each main and side pot, awarding the pots to the winning hands based on
  /// the evaluator. When players tie, the pot is split evenly among the winning
  /// players.
  void showdown();

  /// \brief Handles the action of a player.
  /// \param current_bet The current bet of the hand.
  void handleAction(int current_bet);

  /// \brief Moves the button to the next filled seat.
  void moveButton();

  ~CommunityCard() = default;
};
