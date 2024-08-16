/// \file player_state.hpp
/// \date 2023-28-09
/// \author Elijah Widener Ferreira
///
/// \brief Player class declaration.

#pragma once

#include "MoonPoker/deck.hpp"
#include <vector>

enum ActionIndex
{
  kCheck,
  kCall,
  kFold,
  kRaise,
  kAllInForLess,
  kShortAllIn
};

class PlayerState
{
 public:
  PlayerState(int stack);

  std::vector<Card> getHand();
  int               getTotalBetInRound();
  int               getStack();
  bool              isAllIn();

  void makeBet(int new_bet);
  void resetBetting();
  void moveBetToPot(int amount);
  void dealCards(int num_cards, Deck* deck);
  void subtractStack(int amount);
  void addToStack(int amount);
  int  action(int& current_bet, const int min_bet);
  void addToPot(int current_bet, PlayerState& player);
  void muckCards(std::vector<Card>& muckedCards);

 private:
  int               stack;
  int               total_bet_in_round;
  bool              all_in_flag;
  std::vector<Card> hand;
};