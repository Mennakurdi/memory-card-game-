#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED
#include <iostream>
#include <vector>
#include "C:\Users\lenovo\Desktop\game c++ manon (2)\game c++ manon\game c++\game\Card.h"

using namespace std;
class Deck{
private :
    Card** grid;
    int row ;
    int column;
public:
    Deck(Card** grid ,int row ,int column);
    Deck();
    ~Deck();
    Card** getGrid();
    int getRow();
    int getColumn();
    void setGrid(Card** grid);
    void setRows(int rows);
    void setColumns(int column);
    void shuffle();
    void displayGrid();
    void removeCard(int i, int j) ;
};



#endif // DECK_H_INCLUDED
