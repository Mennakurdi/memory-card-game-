#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

using namespace std;


Card::Card(int number, bool faceup) {
    this->number = number;
    this->faceup = faceup;
}

Card::Card() {
    this->number = 0;
    this->faceup = false;
}

int Card::getNumber() {
    return number;
}

bool Card::getFaceup() {
    return faceup;
}

void Card::setNumber(int number) {
    this->number = number;
}

void Card::setFaceup(bool faceup) {
    this->faceup = faceup;
}

 void Card::display() {
    if (faceup)
        cout << number << " ";
    else
        cout << "* ";
}
  void Card:: Reveal(){
    setFaceup(true);
}
  void Card::hide(){
   setFaceup(false);
}

StandardCard::StandardCard(int number,bool faceup) : Card(number, false) {}
StandardCard::StandardCard() : Card() {}
void StandardCard::display() {
    cout << "Standard card: " << getNumber() << endl;
}
 void StandardCard:: Reveal(){
    setFaceup(true);
}
 void StandardCard::hide(){
    setFaceup(false);
}

BonusCard::BonusCard(int number,bool faceup) : Card(number, false) {}
BonusCard::BonusCard() : Card() {}
void BonusCard::display() {
    cout << "Bonus card: " << getNumber() << endl;
}
 void BonusCard:: Reveal(){
   setFaceup(true);
}
 void BonusCard::hide(){
    setFaceup(false);
}



PenaltyCard::PenaltyCard(int number,bool faceup) : Card(number, false) {}
PenaltyCard::PenaltyCard() : Card() {}
void PenaltyCard::display() {
    cout << "Penalty card: " << getNumber() << endl;
}
 void PenaltyCard:: Reveal(){
   setFaceup(true);
}
 void PenaltyCard::hide(){
    setFaceup(true);
}


Deck::Deck(Card** grid, int row, int column) {
    this->grid = grid;
    this->row = row;
    this->column = column;
}

Deck::Deck() {
    row = 4;
    column = 4;

    grid = new Card*[row];
    for (int i = 0; i < row; i++) {
        grid[i] = new Card*[column];
    }

    int bonusCount = 0;
    int penaltyCount = 0;
    int values[] = {1, 2, 3, 4, 5, 6};
    int valuesSize = 6;
    int valueIndex = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (bonusCount < 2) {
                grid[i][j] = new BonusCard(7, false);
                bonusCount++;
            } else if (penaltyCount < 2) {
                grid[i][j] = new PenaltyCard(8, false);
                penaltyCount++;
            } else {
                grid[i][j] = new StandardCard(values[valueIndex], false);
                valueIndex = (valueIndex + 1) % valuesSize;
            }
        }
    }
}



Deck::~Deck() {
    if (grid) {
        for (int i = 0; i < row; ++i) {
            if (grid[i]) {
                for (int j = 0; j < column; ++j) {
                    delete grid[i][j]; // Delete each card object
                }
                delete[] grid[i];
            }
        }
        delete[] grid;
    }
}


Card** Deck::getGrid() {
    return grid;
}

int Deck::getRow() {
    return row;
}

int Deck::getColumn() {
    return column;
}

void Deck::setGrid(Card** grid) {
    this->grid = grid;
}

void Deck::setRows(int row) {
    this->row = row;
}

void Deck::setColumns(int column) {
    this->column = column;
}

void Deck::displayGrid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].getNumber() == 0) {
                cout << "  ";  // Empty space
            } else if (grid[i][j].getFaceup()) {
                cout << grid[i][j].getNumber() << " ";
            } else {
                cout << "* ";  // Hidden card
            }
        }
        cout << endl;
    }
}
bool Game::isValidSelection(int row, int col) {
    if (row < 0 || row >= deck->getRow() || col < 0 || col >= deck->getColumn()) {
        cout << "Invalid selection. Try again." << endl;
        return false;
    }
    return true;
}
}
  void Deck::removeCard(int row, int col) {
    Card** grid = getGrid();
    grid[row][col].setNumber(0);    // Set the card number to 0
    grid[row][col].hide();          // Ensure the card is face down
    grid[row][col].setFaceup(false); // Logically face down
}
 void Game::takeTurn() {
    int index1, index2;

    // Current player
    Player* currentPlayer = isPlayer1Turn ? p1 : p2;

    // First card selection
    cout << currentPlayer->getName() << ", select the first card (index 0-15): ";
    cin >> index1;

    int row1 = index1 / deck->getColumn();
    int col1 = index1 % deck->getColumn();
    if (!isValidSelection(row1, col1)) return;

    Card** grid = deck->getGrid();
    Card* card1 = &grid[row1][col1];

    if (card1->getFaceup()) {
        cout << "First card already revealed. Choose a different card." << endl;
        return;
    }

    card1->Reveal();
    cout << "Selected first card: ";
    card1->display();

    // Second card selection
    cout << currentPlayer->getName() << ", select the second card (index 0-15): ";
    cin >> index2;

    int row2 = index2 / deck->getColumn();
    int col2 = index2 % deck->getColumn();
    if (!isValidSelection(row2, col2)) return;

    Card* card2 = &grid[row2][col2];

    if (card2->getFaceup()) {
        cout << "Second card already revealed. Choose a different card." << endl;
        return;
    }

    card2->Reveal();
    cout << "Selected second card: ";
    card2->display();

    cout << "\nCurrent grid after revealing cards:" << endl;
    deck->displayGrid();

    // Handle logic
    if (card1->getNumber() == card2->getNumber() && card1->getNumber() > 0) {
        // Standard Cards match
        cout << "Match found! " << currentPlayer->getName() << " gains a point." << endl;
        currentPlayer->increaseScore(1);
        deck->removeCard(row1, col1);
        deck->removeCard(row2, col2);
    }
    else if ((card1->getNumber() == 7 || card1->getNumber() == 8) ||
             (card2->getNumber() == 7 || card2->getNumber() == 8)) {
        // Special Cards handling
        cout << "Special Card revealed!" << endl;

        // Remove the special card, flip the standard card back
        if (card1->getNumber() == 7 || card1->getNumber() == 8) {
            deck->removeCard(row1, col1); // Remove special card
            card2->hide();                // Flip standard card back
        } else {
            deck->removeCard(row2, col2); // Remove special card
            card1->hide();                // Flip standard card back
        }
    }
    else {
        // No match
        cout << "No match. Cards flip back." << endl;
        card1->hide();
        card2->hide();
    }

    // Switch turns
    isPlayer1Turn = !isPlayer1Turn;

    cout << "\nGrid after the turn:" << endl;
    deck->displayGrid();
}


void Deck::shuffle() {

    srand(time(NULL));

    for (int i = 0; i < row * column; ++i) {

        int randRow1 = rand() % row;
        int randCol1 = rand() % column;
        int randRow2 = rand() % row;
        int randCol2 = rand() % column;


        Card temp = grid[randRow1][randCol1];
        grid[randRow1][randCol1] = grid[randRow2][randCol2];
        grid[randRow2][randCol2] = temp;
    }
}


Player::Player(string name, int score) {
    this->name = name;
    this->score = score;
}

Player::Player() {
    this->name = " ";
    this->score = 0;
}

string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

void Player::setName(string name) {
    this->name = name;
}


void Player::increaseScore(int points){
    score+=points;
}
void Player::decreaseScore(int points){
    score-=points;
    }
void Player::displayScore() {
cout << "Player score: " << score << endl;
}
void Player::setScore(int newScore) {
    score=newScore;
}

Game::Game(Player* p1, Player* p2, Deck* deck) {
    this->p1 = p1;
    this->p2 = p2;
    this->deck = deck;
    this->isPlayer1Turn = true;
}

Game::Game() {
    p1 = nullptr;
    p2 = nullptr;
    deck = nullptr;
}

Game::~Game() {}

Player* Game::getP1() {
    return p1;
}

Player* Game::getP2() {
    return p2;
}

Deck* Game::getDeck() {
    return deck;
}

void Game::setPlayer1(Player* p1) {
    this->p1 = p1;
}

void Game::setPlayer2(Player* p2) {
    this->p2 = p2;
}

void Game::setDeck(Deck* deck) {
    this->deck = deck;
}

void Game::initializeGame() {
    if (deck) {
        deck->shuffle();
        cout << "Deck shuffled" << endl;
    } else {
        cout << "Deck does not exist" << endl;
        return;
    }

    if (p1 == nullptr || p2 == nullptr) {
        cout << "One or both players are not set." << endl;
        return;
    }

    deck->displayGrid();

    cout << "Player 1: " << p1->getName() << endl;
    cout << "Player 2: " << p2->getName() << endl;
}

int main() {
    string player1Name, player2Name;

    cout << "Enter Player 1 Name: ";
    cin >> player1Name;

    cout << "Enter Player 2 Name: ";
    cin >> player2Name;
    Player* P1 = new Player(player1Name, 0);
    Player* P2 = new Player(player2Name, 0);
    Deck* deck = new Deck();

    Game G(P1, P2, deck);
    G.initializeGame();

    while (true) {
        // Display current game state
        cout << endl << "Current Scores:" << endl;
        P1->displayScore();
        P2->displayScore();

        // Take a turn
        G.takeTurn();

        bool allMatched = true;
        Card** grid = deck->getGrid();
        for (int i = 0; i < deck->getRow(); ++i) {
            for (int j = 0; j < deck->getColumn(); ++j) {
                if (!grid[i][j].getFaceup()) {
                    allMatched = false;
                    break;
                }
            }
            if (!allMatched) break;
        }

        if (allMatched) {
            cout << "Game Over! All cards have been matched." << endl;

            // Determine the winner
            if (P1->getScore() > P2->getScore()) {
                cout << "Congratulations " << P1->getName() << "! You win!" << endl;
            } else if (P1->getScore() < P2->getScore()) {
                cout << "Congratulations " << P2->getName() << "! You win!" << endl;
            } else {
                cout << "It's a tie! Both players have the same score." << endl;
            }
            break;
        }
    }

    delete P1;
    delete P2;
    delete deck;

    return 0;
}
