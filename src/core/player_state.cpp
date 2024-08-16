/// \file player_state.cpp
/// \date 2023-28-09
/// \author Elijah Widener Ferreira
///
/// \brief Implementation of a "player" at the table.

#include "player_state.hpp"
#include <iostream>

using namespace std;

PlayerState::PlayerState(int stack) :
    stack(stack),
    total_bet_in_round(0),
    all_in_flag(false)
{
}

std::vector<Card>
PlayerState::getHand()
{
  return hand;
}

int
PlayerState::getTotalBetInRound()
{
  return total_bet_in_round;
}

int
PlayerState::getStack()
{
  return stack;
}

bool
PlayerState::isAllIn()
{
  return all_in_flag;
}

void
PlayerState::makeBet(int new_bet)
{
  stack -= new_bet - total_bet_in_round;
  total_bet_in_round = new_bet;
}

void
PlayerState::resetBetting()
{
  total_bet_in_round = 0;
}

void
PlayerState::moveBetToPot(int amount)
{
  total_bet_in_round -= amount;
}

void
PlayerState::dealCards(int num_cards, Deck* deck)
{
  for (int i = 0; i < num_cards; i++) {
    hand.push_back(deck->deal());
  }
}

void
PlayerState::subtractStack(int amount)
{
  stack -= amount;
}

void
PlayerState::addToStack(int amount)
{
  stack += amount;
}

int
PlayerState::action(int& current_bet, const int min_bet)
{
  int  call_amount = current_bet - getTotalBetInRound();
  char playerAction;

  // playerAction = promptPlayerAction(current_bet, min_bet);
  // prompt player action should signal the gui to light up the buttons,
  // and return the action the player chose including the amount if they bet.
  //
  // This also means that the playerConnection will validate the bets
  // This section of code will be morphed into what promptPlayerAction() does
  //=============================TO BE PROMPTPLAYERACTION()=================
  if (current_bet == 0) {
    cout << "'x' to check " << endl;
  }
  if (current_bet != 0) {
    cout << "'c' to call " << call_amount << endl;
  }
  // This conditional check makes it so after a short hand all-in,
  // the most recent player that made a legal raise is not allowed
  // to reraise.
  if (current_bet >= min_bet) {
    cout << "'r' to raise " << endl;
  }

  cout << "'f' to fold " << endl;
  cin >> playerAction;
  cout << "------------------" << endl;
  //=============================TO BE PROMPTPLAYERACTION()=================
  // promptPlayerAction() Should update current_bet by reference once a  user
  // sends a valid bet through the gui

  switch (playerAction) {
    case 'x':
      if (current_bet == 0) {

        return ActionIndex::kCheck;

      } else {
        goto default_case;
      }

    case 'c':
      if (call_amount > stack) {
        cout << "All in for less (" << stack << ")" << endl;
        all_in_flag = true;
        // update call amount if the stack is greater than the call amount but
        // not a legal raise
        call_amount = max(call_amount, stack);
        makeBet(call_amount);
        return ActionIndex::kAllInForLess;
      }
      makeBet(call_amount);
      return ActionIndex::kCall;

    case 'r':

      do {

        // Check if reraise is allowed (after short all-in's)
        if (current_bet < min_bet) {
          goto default_case;
        }

        cout << "Enter amount you want to raise to";

        // Indicate a short all-in
        if (current_bet < min_bet && current_bet == stack) {
          cout << "short all-in (" << stack << ")" << endl;
          all_in_flag = true;
          makeBet(current_bet);
          return ActionIndex::kShortAllIn;
        }
        if (current_bet < min_bet) {
          cout << "Raise must be double the bet or more." << endl;
          cin.clear();
          cin.ignore(100, '\n');
        }
        if (current_bet >= stack) {
          cout << "All in for " << stack << endl;
          current_bet = stack;
          all_in_flag = true;
          makeBet(current_bet);

          return ActionIndex::kRaise;
        }
      } while (current_bet < min_bet);
      makeBet(current_bet);
      return ActionIndex::kRaise;

    case 'f':
      return ActionIndex::kFold;

    default:
    default_case:
      cout << "Invalid input! Please enter a valid action." << endl;
      cin.clear();
      cin.ignore(100, '\n');
      return action(current_bet, min_bet); // Recursive call
                                           // to be changed with validate bet?
  }
}

void
PlayerState::addToPot(int current_bet, PlayerState& player)
{
  int difference            = current_bet - player.total_bet_in_round;
  player.total_bet_in_round = current_bet;
  stack += difference;
}

void
PlayerState::muckCards(std::vector<Card>& muckedCards)
{
  for (size_t i = 0; i < hand.size(); i++) {
    muckedCards.push_back(hand.back());
    hand.pop_back();
  }
}
