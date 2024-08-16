/// \file playerConnection.hpp
/// \date 2023-28-09
/// \author Elijah Widener Ferreira
///
/// \brief Player connection that prompts an http user to take action

#pragma once

#include <MoonPoker/player.hpp>

class AbstractPlayerConnection
{
 public:
  virtual void pureVirtualFunction() = 0; // Pure Virtual Function

  void promptPlayerAction()
  {
    // prompts user
  }

  void changeGameStatus()
  {
    // inactive || spectating <-> active
  }
};
