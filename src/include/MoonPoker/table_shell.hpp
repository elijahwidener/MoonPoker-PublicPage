/// \file table_shell.hpp
/// \date 2023-28-09
///
/// \brief Table unit that all players see.
/// interacts with seats, players and game state to run the poker game

#pragma once

#include <MoonPoker/deck.hpp>

struct GameSettings
{
  int ante;
  int small_blind;
  int big_blind;
  int time;
  int num_cards;
};

class Table
{
 public:
  // ============== Constructors ==============

  Table(Deck& deck, Settings settingsStruct);

  // ============== Utility Methods ===========

  void acceptPlayer(Player& player, Seat seat, int stack) {}

  void kickPlayer(Player& player, ) {}

 private:
  Game game;
  std::map < Player, std::optional<Seat> Players;
  std::array<Seat> seats;
};
