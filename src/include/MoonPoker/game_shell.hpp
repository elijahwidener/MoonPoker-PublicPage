/// \file game_shell.hpp
/// \date 2023-28-09
///
/// \brief A game shell for poker games.

#pragma once

#include <MoonPoker/nlh.hpp>

class Table
{

 public:
  enum GameState
  {
    PRE_FLOP,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN
  };
  // ============== Constructors ==============
  Table(Deck& deck, int numberOfPlayers, int numberOfCards);

  // ============== Constructors Implementation ==============
  Table::Table(Deck& deck, int numberOfPlayers, int numberOfCards) :
      deck(deck),
      gameState(PRE_FLOP),
      handNumber(0),
      pot(0)
  {
    // Initialize players
    players.resize(numberOfPlayers);
  }

  // ============== Getter Methods ============
  GameState getGameState() const { return gameState; }
  int       getHandNumber() const { return handNumber; }
  int       getPot() const { return pot; }

  // ============== Setter Methods ============
  void setGameState(GameState state) { gameState = state; }
  void setHandNumber(int number) { handNumber = number; }
  void setPot(int newPot) { pot = newPot; }
  void setPlayers(const std::vector<Player>& newPlayers)
  {
    players = newPlayers;
  }

  // ============== Action Methods ============
  // Shuffles deck, deals players cards, deals community cards
  void dealNewHand(int numberOfCards, int numberOfPlayers, int button)
  {
    // Shuffle the deck with the mucked cards
    deck.shuffle(muckedCards);
    // clear the mucked cards vector, since they are now in the deck
    muckedCards.clear();

    // deal all cards
    int playersDealt = 0;
    for (int i = button; i < numPlayers; i++) {
      int seatIndex =
        (button + 1 + i) % numPlayers; // Calculate the player index considering
                                       // the dealer position
      players[seatIndex].dealCards(numCardsInNLH); // give the player cards
      inHand.push_back(players[seatIndex]);        // put the player in the hand
      ++playersDealt;

      if (playersDealt == numPlayers) {
        break; // Exit the loop when all players have been dealt
      }
    }

    for (int k = 0; k < 5; i++) {
      communityCards.push_back(deck->deal());
    }
  };
  void showCards(int index, int numberOfCards)
  {
    for (int i = index; i < numberOfCards; i++) {
      cout << communityCards[i] << ",";
    }
    cout << endl;
  }
  void awardMainPot()
  {
    // Implement logic to distribute main pot to player,
    // using main pot for flexibility with side pot
  }
  // puts cards into the muck pile, and removes them from the hand.

  // ============== Utility Methods ===========
  void muckCommunityCards(int numberOfCards)
  {
    // Add the mucked card to the mucked card vector, then remove it form the
    // communityCards
    for (int i = 0; i < numberOfCards; i++) {
      muckedCards.push_back(communityCards.back());
      communityCards.pop_back();
    }
  };
  void muckPlayerCards(Player& player, int numberOfCards)
  {
    // Fetch the player's hand
    std::vector<Card> playerHand = player.getHand();

    // Add the mucked cards to the mucked card vector, then remove them from the
    // player's hand
    for (int i = 0; i < numberOfCards; i++) {
      muckedCards.push_back(playerHand.back());
      playerHand.pop_back();
    }

    // Update the player's hand
    player.setHand(playerHand);
  }
  void addToPot(int currentBet, Player& player)
  {
    int difference         = currentBet - player.totalBetInRound;
    player.totalBetInRound = currentBet;

    pot += difference;
  }

  // ============== Private Members ===========

 private:
  GameState           gameState;
  int                 handNumber;
  int                 pot;
  int                 button;
  std::vector<Card>   communityCards;
  std::vector<Card>   muckedCards;
  std::vector<Player> players;
};
