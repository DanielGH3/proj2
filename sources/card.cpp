#include <card.hpp>
#include <string>
using namespace std;
using namespace ariel;

Card::Card(int value, string symbol){
    this->value = value;
    this->symbol = symbol;
}

string Card::getSymbol(){
    return symbol;
}

int Card::getValue(){
    return value;
}