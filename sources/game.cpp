#include <game.hpp>
#include <player.hpp>
#include <card.hpp>
#include <stdlib.h>
#include <string>
#include <stack>
#include <cstdlib> 

using namespace std;
using namespace ariel;

int cards[52];
int available = 0;

int setseed = 0;

int getRandomCard(){
    if(available == 0) {
        available = 52;
        for(int i = 0; i < 52; i++){
            cards[i] = i;
        }     
    }

    int index = rand() % available;
    int value = cards[index];

    int temp = cards[available - 1];
    cards[available - 1] = cards[index];
    cards[index] = temp;
    available--;

    return value;
}

string getSymbol(int value){
    if(value <= 13) return "diamond";
    if(value <= 26) return "spades";
    if(value <= 39) return "hearts";
    return "clubs";
}


Game::Game(Player& P1, Player& P2) {
    if(!setseed){
        srand(time(NULL));
        setseed = 1;
    }

    p1 = &P1;
    p2 = &P2;
    turns = "";
    lasturn = "";

    playAgain();
}

void Game::playAgain(){
    p1->clearDeck();
    p2->clearDeck();

    for(int i = 0; i < 26; i++){
        //TODO : SORT FILES BETWEEN PLAYERS
        int card1 = getRandomCard();
        int card2 = getRandomCard();
        CardPtr c1 = new Card(card1 % 13 + 1, getSymbol(card1 + 1));
        CardPtr c2 = new Card(card2 % 13 + 1, getSymbol(card2 + 1));
        p1->addCard(c1);
        p2->addCard(c2);
    }
}

void Game::addToLastTurn(CardPtr c1, CardPtr c2){
    lasturn += p1->getName() + " played ";
    switch (c1->getValue())
    {
        case 1: lasturn += "ace"; break;
        case 11: lasturn += "jack"; break;
        case 12: lasturn += "queen"; break;
        case 13: lasturn += "king"; break;
        default: lasturn += to_string(c1->getValue());
    }
    lasturn += " of " + c1->getSymbol();
    lasturn += ", " + p2->getName() + " played ";
    switch (c2->getValue())
    {
        case 1: lasturn += "ace"; break;
        case 11: lasturn += "jack"; break;
        case 12: lasturn += "queen"; break;
        case 13: lasturn += "king"; break;
        default: lasturn += to_string(c2->getValue());
    }
    lasturn += " of " + c2->getSymbol();
}

void Game::playTurn(){
    stack<CardPtr> cards1;
    stack<CardPtr> cards2;
    CardPtr c1 = p1->getTopCard();
    CardPtr c2 = p2->getTopCard();  
    if(c1 != NULL) cards1.push(c1);
    if(c2 != NULL) cards2.push(c2);
    lasturn.clear();
    addToLastTurn(c1, c2);

    if(c1 != NULL && c2 != NULL){
        if(c1->getValue() == c2->getValue()){
            p1->normalInc();
            p2->normalInc();
        }
        while(c1->getValue() == c2->getValue()){
            lasturn += ", TIE!";
            p1->tiesInc(); 
            p2->tiesInc();

            //FACE DOWN CARD
            c1 = p1->getTopCard();
            c2 = p2->getTopCard();  
            if(c1 != NULL) cards1.push(c1);
            if(c2 != NULL) cards2.push(c2);
            if(c1 == NULL || c2 == NULL){
                break;
            }
            lasturn += "\nboth players added upsidedown cards";

            //FACE UP CARD
            c1 = p1->getTopCard();
            c2 = p2->getTopCard();  
            if(c1 != NULL) cards1.push(c1);
            if(c2 != NULL) cards2.push(c2);
            if(c1 == NULL || c2 == NULL){
                break;
            }
            lasturn += "\n";
            addToLastTurn(c1, c2);
        }
    }

    //RETURN CARDS TO EACH PALYER
    if(c1 == NULL || c2 == NULL){
        lasturn += ", not enough cards to continue.";
        while(!cards1.empty()){
            p1->takeCard(cards1.top());
            cards1.pop();
        }
        while(!cards2.empty()){
            p2->takeCard(cards2.top());
            cards2.pop();
        }
    }else{//WINNER TAKES
        if((c1->getValue() == 1 && c2->getValue() != 2) || (!(c2->getValue() == 1 && c1->getValue() != 2) && c1->getValue() > c2->getValue())){
            lasturn += ", " + p1->getName() + " won the round!";
        }else{
            lasturn += ", " + p2->getName() + " won the round!";
        }
        while(!cards1.empty()){
            if(c1->getValue() > c2->getValue()){
                p1->takeCard(cards1.top());
            }else{
                p2->takeCard(cards1.top());
            }
            cards1.pop();
        }
        while(!cards2.empty()){
            if(c1->getValue() > c2->getValue()){
                p1->takeCard(cards2.top());
            }else{
                p2->takeCard(cards2.top());
            }
            cards2.pop();
        }
    }

    turns += lasturn + "\n\n";
}

void Game::printLastTurn(){
    printf("%s\n", lasturn.c_str());
}

void Game::playAll(){
    while(p1->stacksize() > 0 && p2->stacksize() > 0){
        playTurn();
    }

    if(p1->cardesTaken() > p2->cardesTaken()){
        p1->winsInc(); p2->lossesInc();
    }else if (p2->cardesTaken() > p1->cardesTaken()){
        p1->lossesInc(); p2->winsInc();
    }else{
        p1->winsInc();
        p2->winsInc();
    }
}

void Game::printWiner(){
    if(p1->cardesTaken() > p2->cardesTaken()){
        printf("the winner is %s!\n", p1->getName().c_str());
    }else if (p2->cardesTaken() > p1->cardesTaken()){
        printf("the winner is %s!\n", p2->getName().c_str());
    }else{
        printf("the game was a tie!.\n");
    }
}

void Game::printLog(){
    printf("%s", turns.c_str());
}

void Game::printStats(){
    printf("____________STATS____________\n");
    printf("%s : \n", p1->getName().c_str());
    printf("\tCards taken : %d\n", p1->cardesTaken());
    printf("\tWins : %d, Losses : %d, Winrate : %f%%\n", p1->getWins(), p1->getLosses(), p1->getWinrate() * 100);
    printf("\tDraws : %d, Normal : %d, Drawrate : %f%%\n", p1->getTies(), p1->getNormal(), p1->getDrawrate() * 100);

    printf("\n%s : \n", p2->getName().c_str());
    printf("\tCards taken : %d\n", p2->cardesTaken());
    printf("\tWins : %d, Losses : %d, Winrate : %f%%\n", p2->getWins(), p2->getLosses(), p2->getWinrate() * 100);
    printf("\tDraws : %d, Normal : %d, Drawrate : %f%% \n", p2->getTies(), p2 ->getNormal(), p2->getDrawrate() * 100);
}