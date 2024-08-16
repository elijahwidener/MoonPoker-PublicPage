/// \file game_experimental.hpp
/// \date 2023-10-24
/// \author MoonPoker Development Team (moonpoker@msplib.com)
///
/// \brief Experimental implementation of Game class heirarchy.

#pragma once

#ifndef __cplusplus
#error "game_experimental.hpp is a cxx-only header."
#endif // __cplusplus

// ======================= Public Interface ==========================

/// \brief The interface for a game.
class Game
{
 public:
  virtual void PlayRound() = 0;
};

class CommunityCardPoker : public Game
{
 public:
  virtual void PlayRound() override
  {
    dealCards();
    playBettingRound();
    dealFlop();
    playBettingRound();
    dealTurn();
    playBettingRound();
    dealRiver();
    playBettingRound();
    playShowdown();
  }

 protected:
  virtual void dealCards()        = 0;
  virtual void playBettingRound() = 0;
  virtual void playShowdown()     = 0;
  virtual void dealFlop()         = 0;
  virtual void dealTurn()         = 0;
  virtual void dealRiver()        = 0;
};

template<class HandType, class BetType, class... HandEvaluators>
class CommunityCardPokerImpl : public CommunityCardPoker
{
  ....
};

class TexasHoldem :
    public CommunityCardPokerImpl<
      std::array<Card, 5>,
      NoLimitBet,
      HandEvaluator>
{
};

// ===================== Detail Implementation =======================
