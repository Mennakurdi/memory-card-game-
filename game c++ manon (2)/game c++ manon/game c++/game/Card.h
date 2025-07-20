#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include <string>
#include <iostream>
using namespace std;
class Card{
  private :
    int number ;
    bool faceup;
  public:
    Card(int number ,bool faceup);
    Card();
    int getNumber();
    bool getFaceup();
    void setNumber(int number);
    void setFaceup(bool faceup);
    virtual void display();
    virtual void Reveal();
    virtual void hide();

class StandardCard : public Card {
public :
    StandardCard(int number,bool faceup);
    StandardCard();
    void display();
    void Reveal();
    void hide();

};
class BonusCard : public Card {
public :
    BonusCard(int number,bool faceup);
    BonusCard();
    void display();
    void Reveal();
    void hide();
};
class PenaltyCard : public Card{
public :
    PenaltyCard(int number,bool faceup );
    PenaltyCard();
    void display();
    void Reveal();
    void hide();

};




#endif // CARD_H_INCLUDED
