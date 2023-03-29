#include <player.hpp>
#include <string>
#include <stack>

using namespace std;
using namespace ariel;

Player::Player(string name){
    this->name = name;
    wins = 0;
    losses = 0;
    ties = 0;
    normal = 0;
}

Player::~Player(){
    while(!cards.empty()){
        CardPtr p = cards.top();
        cards.pop();
        delete p;
    }
    while(!takenCards.empty()){
        CardPtr p = takenCards.top();
        takenCards.pop();
        delete p;
    }
}

int Player::stacksize(){
    return cards.size();
}

int Player::cardesTaken(){
    return takenCards.size();
}


void Player::clearDeck(){
    while(!cards.empty()){
        cards.pop();
    }
}

void Player::addCard(CardPtr card){
    cards.push(card);
}

void Player::takeCard(CardPtr card){
    takenCards.push(card);
}

CardPtr Player::getTopCard(){
    if(cards.empty()) return NULL;
    CardPtr temp = cards.top();
    cards.pop();
    return temp;
}

string Player::getName(){
    return name;
}

double Player::getWinrate(){
    if(wins + losses == 0) return 0;
    return (double)wins / (wins + losses);
}
double Player::getDrawrate(){
    if(ties + normal == 0) return 0;
    return (double)ties / (ties + normal);
}

int Player::getWins(){
    return wins;
}
int Player::getLosses(){
    return losses;
}
int Player::getTies(){
    return ties;
}
int Player::getNormal(){
    return normal;
}
void Player::winsInc(){
    wins++;
}
void Player::lossesInc(){
    losses++;
}
void Player::tiesInc(){
    ties++;
}
void Player::normalInc(){
    normal++;
}