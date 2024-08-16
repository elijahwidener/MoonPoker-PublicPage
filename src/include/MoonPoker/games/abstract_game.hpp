/// \file abstract_game.hpp
/// \date 2023-11-23
/// \author Elijah Widener Ferreira
///
/// \brief Class for Games.
#pragma once

#include "MoonPoker/evaluators/hand_evaluator.hpp"
#include "MoonPoker/seat.hpp"
#include <memory>

/// \brief Represents an abstract game in Moon Poker.
///
/// \details The Game class provides a base for implementing different poker
/// games It contains common data members and functions that are shared among
/// different game types. Derived classes must implement the pure virtual
/// function playHand() to run users through a single hand.
class Game
{
 protected:
  int ante;
  int small_blind;
  int big_blind;
  int num_cards;
  int button;
  int min_bet;
  std::vector<std::pair<int, std::vector<std::reference_wrapper<PlayerState>>>>
                                                   pots;
  Deck                                             deck;
  std::vector<Card>                                board;
  std::vector<Card>                                mucked_cards;
  std::vector<std::reference_wrapper<PlayerState>> players_in_hand;
  std::unique_ptr<HandEvaluator>                   evaluator;

 public:
  /// \brief Constructor with implementation for Game.
  Game(
    int                            ante,
    int                            small_blind,
    int                            big_blind,
    int                            num_cards,
    std::unique_ptr<HandEvaluator> evaluator);

  /// \brief Plays a single hand of the game.
  virtual void playHand() = 0;

  /// \brief Indicates user entry is a valid bet.
  ///
  /// \details When true, the raise button will be light up and a
  /// user will have the capability to click it, confirming and sending their
  /// bet. When false, the raise button will not be light up, and a user will
  /// not be able to send their raise. Additionally, the part of the user UI
  /// where people enter their bet will be light up red, further indicating
  /// they can't make the bet
  /// \note All parameters ought to be passed in terms of big blinds.
  /// \remark float min_bet = std::max(1, previous_raise + (2 * previous_raise_delta));
  ///
  /// \param bet_size The size of the players attempted bet.
  /// \param min_bet A min raise is always the amount of the last legal raise,
  /// plus two times the "raise delta" of said raise. The raise delta is the
  /// actual amount increased. EX: a bet is 10, and someone raised
  /// to 25, the raise delta is 15.
  /// \param max_bet The max a specific player can bet.
  /// \return True if valid bet, false otherwise.
  static bool validateBet(float bet_size, float min_bet, float max_bet);

  /// @brief Adds chips to the pot, creating side pots when necessary.
  /// @param amount The amount of chips to add to the pot.
  void addToPot(int amount);

  /// \brief Collects bets from players and adds them to the pot, creating side
  /// pots when necessary.
  /// \param current_players Players still in the hand.
  /// \details This function is called after a round of betting ends, as signaled
  /// by \ref Game::closeAction(). When first called, current_round_players will
  /// be the players_in_hand vector. It is OK that all-in players are still in
  /// this vector, as they will be skipped over. This function may recursively
  /// call itself to manage the creation of side pots. Each recursive call
  /// handles the formation of a new side pot. The function achieves this by
  /// appending a new std::pair<int, std::vector<R_W<PlayerState>>> to the pots
  /// vector. This pair represents a side pot, where the first element is the
  /// pot's chip count and the second element is the list of players eligible to
  /// win from that pot. The function ensures accurate allocation of chips to
  /// the main and side pots based on the players' bets.
  void collectBets(
    std::vector<std::reference_wrapper<PlayerState>> current_players);

  /// \brief Indicates if the action is closed.
  ///
  /// \details Action is closed when all players have either matched the bet,
  /// folded, or are all in.
  /// \param players Players still in the hand.
  /// \param current_bet The amount players need to have called.
  /// \return True if the action is closed, false otherwise.
  bool closeAction(const int current_bet);

  /// \brief Updates the minimum bet size.
  /// \param current_bet The current bet in a round.
  void updateMinBet(const int current_bet);

  /// \brief Awards player a pot, adding it to their stack, and removes that
  /// amount from the pot
  /// \param player The player winning chips.
  /// \param pot_amount The amount of chips to be won.
  /// \param pot_index The index of the pot were dealing with in the pots vector.
  void awardPot(PlayerState& player, float pot_amount, int pot_index);

  // Destructor
  virtual ~Game() = default;
};
