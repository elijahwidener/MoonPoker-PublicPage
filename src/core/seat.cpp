/// \file seat.cpp
/// \date 2023-28-09
/// \brief Implementation of  that players can "sit" in to play at the table.

#include "seat.hpp"

Seat::Seat() : stack(0), active(false) {}

std::reference_wrapper<PlayerState>
Seat::getPlayer()
{
  if (player) {
    return std::ref(*player);
  } else {
    throw std::runtime_error("No player in seat");
  }
}

void
Seat::seatPlayer(PlayerState& player, int stack)
{
  if (!active) {
    this->player = std::move(player); // Transfer ownership
    this->player->addToStack(stack);
    sitDown();
  }
}

void
Seat::standUp()
{
  active = false;
}

void
Seat::sitDown()
{
  active = true;
}

bool
Seat::isActive() const
{
  return active;
}

void
Seat::leaveSeat()
{
  standUp();
  player.reset(); // Automatically deletes the object and sets to nullptr
}

void
Seat::topOff(int amount)
{
  if (player) {
    player->addToStack(amount);
  }
}
