#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include<string>
using namespace std;
class Player{
private :
    string name;
    int score;
public :
    Player(string name,int score);
    Player();
    string getName();
    int  getScore();
    void setName(string name);
    void setScore(int newScore);
    void displayScore();
    void increaseScore(int value);
    void decreaseScore(int value);

};



#endif
