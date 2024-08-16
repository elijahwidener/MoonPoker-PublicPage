/// \file no_limit_holdem.cpp
/// \date 2023-12-20
/// \author Elijah Widener Ferreira
///
/// \brief Concrete implementation of the No Limit Hold'em game.

#include "games/no_limit_holdem.hpp"

NoLimitHoldem::NoLimitHoldem(int ante, int small_blind, int big_blind) :
    CommunityCard(
      ante,
      small_blind,
      big_blind,
      2,
      std::make_unique<StandardEvaluator>())
{
}

void
NoLimitHoldem::playHand()
{

  populatePlayersInHand();

  // Pre-flop betting street
  // Deck is shuffle/dealt and blinds get posted here
  bettingStreet();
  collectBets(players_in_hand);

  // Deal the flop (3 cards)
  dealCardToBoard();
  dealCardToBoard();
  dealCardToBoard();

  // Flop betting street
  bettingStreet();
  collectBets(players_in_hand);

  // Deal the turn
  dealCardToBoard();

  // Turn betting street
  bettingStreet();
  collectBets(players_in_hand);

  // Deal the river
  dealCardToBoard();

  // River betting street
  bettingStreet();
  collectBets(players_in_hand);

  // If we have gotten here, there is more than one player in the hand, and we
  // are ready for showdown.
  showdown();

  muckCommunityCards();
  moveButton();
}