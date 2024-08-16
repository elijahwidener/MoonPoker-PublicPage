/// \file seat.hpp
/// \date 2023-28-09
/// \brief Seat that players can "sit" in to play at the table.
// The seat contains a player's stack, and acts as the owner of the stack.

#pragma once

#ifndef __cplusplus
#error "seat.hpp is a cxx-only header."
#endif // __cplusplus

#include "MoonPoker/player_state.hpp"
#include <functional>
#include <optional>

class Seat
{
 public:
  Seat();

  /// \brief Returns the player in the seat.
  /// \return A reference the player in the seat.
  /// \note
  std::reference_wrapper<PlayerState> getPlayer();

  /// \brief Seats a player.
  /// \param player A pointer to the player to be seated.
  /// \param stack The players buy-in.
  void seatPlayer(PlayerState& player, int stack);

  /// \brief Stands up the player in the seat, setting the seat to inactive.
  void standUp();

  /// \brief Sits down the player in the seat, setting the seat to active.
  void sitDown();

  /// \brief Empties the seat.
  /// \details Stands up the player in the seat, and sets the player pointer to nullptr
  void leaveSeat();

  /// \brief Returns if the seat is filled and the player active
  /// \return True if the seat is filled and the player active, false otherwise.
  bool isActive() const;

  /// \brief Adds chips to the player's stack.
  void topOff(int amount);

 private:
  std::optional<PlayerState> player;
  int                        stack;
  bool                       active;
};
