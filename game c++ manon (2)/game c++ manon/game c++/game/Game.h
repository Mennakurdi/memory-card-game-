#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Deck.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

class Game {
private:

    Player* p1;
    Player* p2;
    Deck* deck;
    bool isPlayer1Turn;

public:
    Game(Player* p1, Player* p2, Deck* deck);
    Game();
    ~Game();
    Player* getP1();
    Player* getP2();
    Deck* getDeck();
    void setPlayer1(Player* p1);
    void setPlayer2(Player* p2);
    void setDeck(Deck* deck);
    void initializeGame();
    void takeTurn();
    void handleBonusCard(Card* card1, Card* card2);
    void handlePenaltyCard(Card* card1, Card* card2);
    void playerScoreUpdate(int points);
    void displayScores();
    bool isGameOver();

};



#endif // GAME_H_INCLUDED
