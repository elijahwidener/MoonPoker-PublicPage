/// \file seat_shell.hpp
/// \date 2023-28-09
///
/// \brief Seat that players can "sit" in to play
/// at the table. The seat contains a players stack, and acts
/// as the owner of the stack.

#pragma once

#include <MoonPoker/player.hpp>

class Seat
{
 public:
  // ============== Constructors ==============

  Seat(Player Player, int stack, bool active);

  // ============== Utility Methods ===========

  void fillSeat(Player& player, ) {}

  void standUp(Player& player, ) {}

  void leaveSeat(Player& player, ) {}

  void topOff(Player& player, int amount) {}

 private:
  int              stack;
  bool inHand bool active;
};
