/// \file community_card_structure.cpp
/// \date 2023-11-19
/// \author Elijah Widener Ferreira
///
/// \brief Implementation of basic structure of community card games.

#include "games/community_card_structure.hpp"

void
CommunityCard::populatePlayersInHand()
{
  players_in_hand.clear();

  for (int i = 1; i <= kMaxPlayers; i++) {
    // Button should be the last player to act in the hand, meaning they are the
    // last player to be added to the players_in_hand vector.
    // Therefore, we start at the button + 1, and iterate through seats 9
    // times, skipping over empty seats and inactive players.
    if (seats[(button + i) % kMaxPlayers].isActive()) {
      players_in_hand.push_back(seats[(button + i) % kMaxPlayers].getPlayer());
    }
  }
}

void
CommunityCard::dealAndPostBlinds()
{

  // Initialize Variables
  int player_count = 0;

  // Shuffle and deal cards
  deck.shuffle(mucked_cards);
  for (PlayerState& player : players_in_hand) {
    player.dealCards(num_cards, &deck);
    if (ante != 0) {
      player.subtractStack(ante);
    }
    player_count++;
  }
  pots[0].first += ante * player_count;

  // In heads up, the button is the small blind, and the other player is the big
  if (player_count == 2) {
    // Post small blind
    players_in_hand[1].get().makeBet(small_blind);
    // Post big blind
    players_in_hand[0].get().makeBet(big_blind);
  } else {
    // Post small blind
    players_in_hand[0].get().makeBet(small_blind);
    // Post big blind
    players_in_hand[1].get().makeBet(big_blind);
  }
}

void
CommunityCard::dealCardToBoard()
{
  board.push_back(deck.deal());
}

void
CommunityCard::muckCommunityCards()
{
  for (Card& card : board) {
    mucked_cards.push_back(card);
  }
  board.clear();
}

void
CommunityCard::resetStreet()
{
  for (PlayerState& player : players_in_hand) {
    player.resetBetting();
  }
  min_bet        = big_blind;
  actions_on_you = players_in_hand.begin();
}

void
CommunityCard::bettingStreet()
{
  resetStreet(); // min_bet is reset here as well
  int current_bet = 0;

  // If the pot is empty, its preflop, and we need to deal and post blinds
  if (pots[0].first == 0) {
    dealAndPostBlinds();
    updateMinBet(big_blind);
    actions_on_you = players_in_hand.begin() + 2;
  }

  /// \note:When actions_on_you reaches the end of players_in_hand,
  /// it is equivalent to the iterator pointing just past the last element.
  /// Therefore, the last player will have their action handled before
  /// actions_on_you equals players_in_hand.end().
  while (actions_on_you != players_in_hand.end()) {
    if (actions_on_you->get().isAllIn()) {
      actions_on_you++;
      continue;
    }
    actions_on_you->get().action(current_bet, min_bet);
    handleAction(current_bet);
  }
  while (!closeAction(current_bet)) {
    actions_on_you = players_in_hand.begin();
    while (actions_on_you != players_in_hand.end()) {
      if (
        actions_on_you->get().getTotalBetInRound() != current_bet &&
        !((actions_on_you->get().isAllIn()))) {
        actions_on_you->get().action(current_bet, min_bet);
        handleAction(current_bet);
      } else {
        actions_on_you++;
      }
    }
  }
}

void
CommunityCard::showdown()
{
  int current_pot_index = 0;
  for (auto& [pot_amount, eligible_players] : pots) {
    std::vector<std::reference_wrapper<PlayerState>> winners;
    long long                                        highest_hand = 0;

    for (PlayerState& player : eligible_players) {
      long long player_strength =
        evaluator->evaluateHand(player.getHand(), board);
      if (player_strength == highest_hand) {
        winners.push_back(std::ref(player));
      } else if (player_strength > highest_hand) {
        highest_hand = player_strength;
        winners.clear();
        winners.push_back(std::ref(player));
      };
    }
    // Award the pot to the winners(s)
    for (auto& winner_ref : winners) {
      PlayerState& winner          = winner_ref.get();
      float        winnings_amount = pot_amount / winners.size();
      awardPot(winner, winnings_amount, current_pot_index);
    }
    current_pot_index++;
  }
}

void
CommunityCard::handleAction(int current_bet)
{
  // these values are temporary, just here so the project builds for now
  int fold, check, call, raise = 0;

  if (fold) {

    int pot_index = 0;

    for (auto& [pot_amount, eligible_players] : pots) {
      // Remove the folding player from the eligible players vector
      eligible_players.erase(actions_on_you);
      // If there is only one player left in the eligible players vector, they
      // win that pot.

      // \note: consider removing and handling this at showdown
      if (eligible_players.size() == 1) {
        awardPot(eligible_players[0], pot_amount, pot_index);
      }
      pot_index++;
    }
    // Remove the folding player
    players_in_hand.erase(actions_on_you);
    // We do not need to increment actions_on_you because erasing an element
    // from a vector shifts everything else down one index.

    // If only one player is left in players_in_hand, then we have awarded all
    // pots and are done with this hand, so we return.
    if (players_in_hand.size() == 1) {
      return;
    }

  } else if (check) {
    // Next player's turn
    actions_on_you++;

  } else if (call) {
    int betAmount = current_bet - actions_on_you->get().getTotalBetInRound();
    actions_on_you->get().makeBet(betAmount);
    // Next player's turn
    actions_on_you++;

  } else if (raise) {
    int raise_amount; // \todo: How to implement user input
    actions_on_you->get().makeBet(raise_amount);
    // If the all in constitutes a legal raise, update min bet
    if (actions_on_you->get().getTotalBetInRound() > min_bet) {
      updateMinBet(actions_on_you->get().getTotalBetInRound());
    }
    // Next player's turn
    actions_on_you++;
  }
}

// Some possible infinite loops if all players are inactive
void
CommunityCard::moveButton()
{
  button = (button + 1) % 9;
  // Keep moving the button until we find an active player
  while (!seats[button].isActive()) {
    button = (button + 1) % 9;
  }
}