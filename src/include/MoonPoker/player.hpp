/// \file player.hpp
/// \date 2023-28-09
/// \author Elijah Widener Ferreira
///
/// \brief Temporary player class that will eventually
/// be morphed into an action class.

#pragma once

#ifndef __cplusplus
#error "player.hpp is a cxx-only header."
#endif // __cplusplus

#include <MoonPoker/deck.hpp>

using namespace std;

/// \brief Special integer-convertible action indices for player actions.
enum ActionIndex
{
  kCheck,
  kCall,
  kFold,
  kRaise,
  kAllInForLess,
  kShortAllIn
};
class Player
{
 public:
  // ============== Constructors Implementation ==============
  Player(Deck& deck, int numberOfCards, int bet, int stack) :
      deck(&deck),
      numberOfCards(numberOfCards),
      bet(bet),
      stack(stack),
      totalBetInRound(0),
      allInFlag(false)
  {
    dealCards(numberOfCards);
  }

  // ============== Getter Methods ============
  vector<Card> getCards() { return hand; }
  int          getBet() { return bet; }
  int          getTotalBetInRound() { return totalBetInRound; }
  bool         isAllIn() { return allInFlag; }

  // ============== Setter Methods ============
  void makeBet(int newBet)
  {
    bet = newBet;
    stack -= newBet;
  }

  void resetBetting()
  {
    bet             = 0;
    totalBetInRound = 0;
  }

  // ============== Action Methods ============

  // Deals a player two distinct random cards using the Deck class
  void dealCards(int numberOfCards)
  {
    // Add the mucked card to the mucked card vector, then remove from hand
    for (int i = 0; i < numberOfCards; i++) {
      hand.push_back(deck->deal());
    }
  };

  // Asks player for action, handles Check, Call, Raise, Fold
  int action(
    vector<Card>& muckedCards,
    int           currentBet,
    int           numberOfCards,
    int           minRaiseDelta,
    int           bigBlind)
  {
    int  minRaise       = std::max(bigBlind, (currentBet + minRaiseDelta));
    int  callAmount     = currentBet - getTotalBetInRound();
    bool disableReRaise = false;
    char playerAction;

    if (currentBet == 0) {
      cout << "'x' to check " << endl;
    }
    if (currentBet != 0) {
      cout << "'c' to call " << callAmount << endl;
    }
    // This conditional check makes it so after a short hand all-in,
    // the most recent player that made a legal raise is not allowed
    // to reraise.
    if (currentBet >= getTotalBetInRound() + minRaiseDelta) {
      cout << "'r' to raise " << endl;
    }

    cout << "'f' to fold " << endl;
    cin >> playerAction;
    cout << "------------------" << endl;

    switch (playerAction) {
      case 'x':
        if (currentBet == 0) {

          return ActionIndex::kCheck;

        } else {
          goto default_case;
        }

      case 'c':
        if (callAmount > allIn()) {
          cout << "All in for less (" << stack << ")" << endl;
          callAmount = allIn();
          makeBet(callAmount);

          return ActionIndex::kAllInForLess;
        }
        makeBet(callAmount);
        return ActionIndex::kCall;

      case 'r':

        do {

          // Check if reraise is allowed (after short all-in's)
          if (currentBet < getTotalBetInRound() + minRaiseDelta) {
            goto default_case;
          }

          cout << "Enter amount you want to raise to";
          cin >> currentBet;

          // Indicate a short all-in
          if (currentBet < minRaise && currentBet == stack) {
            cout << "short all-in (" << stack << ")" << endl;
            allInFlag = true;
            makeBet(currentBet);

            return ActionIndex::kShortAllIn;
          }
          if (currentBet < minRaise) {
            cout << "Raise must be double the bet or more." << endl;
            cin.clear();
            cin.ignore(100, '\n');
          }
          if (currentBet >= stack) {
            cout << "All in for " << stack << endl;
            currentBet = stack;
            allInFlag  = true;
            makeBet(currentBet);

            return ActionIndex::kRaise;
          }
        } while (currentBet < minRaise);
        makeBet(currentBet);
        return ActionIndex::kRaise;

      case 'f':
        muckCards(numberOfCards, muckedCards);
        return ActionIndex::kFold;

      default:
      default_case:
        cout << "Invalid input! Please enter a valid action." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        return action(
          muckedCards, currentBet, numberOfCards, minRaiseDelta, bigBlind);
        // Recursive call
    }
  }

  // Player goes all in
  int allIn()
  {
    allInFlag = true;
    return stack;
  }

  void winPot(Player& dealer)
  {
    stack += dealer.stack;
    dealer.stack = 0;
  }

  void addToPot(int currentBet, Player& player)
  {
    int difference         = currentBet - player.totalBetInRound;
    player.totalBetInRound = currentBet;

    // Add to stack
    stack += difference;
  }

  void muckCards(int numberOfCards, vector<Card>& muckedCards)
  {
    // Add the mucked card to the mucked card vector, then remove from hand
    for (int i = 0; i < numberOfCards; i++) {
      muckedCards.push_back(hand.back());
      hand.pop_back();
    }
  };

  // ============== Private Members ===========
 private:
  int               numberOfCards, bet, stack, totalBetInRound;
  bool              allInFlag;
  Deck*             deck;
  std::vector<Card> hand;
  std::vector<Card> muckedCards;
};
