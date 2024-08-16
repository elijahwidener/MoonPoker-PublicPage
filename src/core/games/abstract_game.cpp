/// \file abstract_game.cpp
/// \date 2023-11-23
/// \author Elijah Widener Ferreira
///
/// \brief Class implementation for Games.

#include "games/abstract_game.hpp"

Game::Game(
  int                            ante,
  int                            small_blind,
  int                            big_blind,
  int                            num_cards,
  std::unique_ptr<HandEvaluator> evaluator) :
    ante{ante},
    small_blind{small_blind},
    big_blind{big_blind},
    num_cards{num_cards},
    button{0},
    deck{},
    evaluator{std::move(evaluator)}
{
}

bool
Game::validateBet(float bet_size, float min_bet, float max_bet)
{
  if (bet_size == max_bet || (bet_size >= min_bet && bet_size <= max_bet)) {
    return true;
  }
  return false;
}

void
Game::collectBets(
  std::vector<std::reference_wrapper<PlayerState>> current_round_players)
{
  std::vector<std::reference_wrapper<PlayerState>> side_pot_players;
  int current_pot_index = pots.size() - 1;

  // find the lowest bet among the players
  int lowest_bet = current_round_players[0].get().getTotalBetInRound();
  for (PlayerState& player : current_round_players) {
    if (player.getTotalBetInRound() < lowest_bet) {
      lowest_bet = player.getTotalBetInRound();
    }
  }

  for (PlayerState& player : current_round_players) {
    // skip over players who may already be all in, or when action checks around
    if (player.getTotalBetInRound() == 0) {
      continue;
    } else {
      pots[current_pot_index].first += lowest_bet;
      // subtract the lowest bet from the player's total bet in round
      player.moveBetToPot(lowest_bet);
      // If a player has chips remaining, that means we will need a side pot,
      // and we will call this function recursively.
      if (player.getTotalBetInRound() > 0) {
        side_pot_players.push_back(std::ref(player));
      }
    }
  }
  if (side_pot_players.size() > 0) {
    std::pair<int, std::vector<std::reference_wrapper<PlayerState>>> side_pot{
      0, side_pot_players};
    pots.push_back(side_pot);
    collectBets(side_pot_players);
  }
}

bool
Game::closeAction(const int current_bet)
{
  for (PlayerState& player : players_in_hand) {
    if (player.getTotalBetInRound() != current_bet && !player.isAllIn()) {
      return false;
    }
  }
  return true;
}

void
Game::updateMinBet(const int current_bet)
{
  min_bet += (current_bet - min_bet) * 2;
}

void
Game::awardPot(PlayerState& player, float pot_amount, int pot_index)
{
  player.addToStack(pot_amount);
  pots[pot_index].first -= pot_amount;
}