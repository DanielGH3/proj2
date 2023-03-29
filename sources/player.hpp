#include <string>
#include "card.hpp"
#include <stack>

#ifndef PLAYER_
#define PLAYER_

namespace ariel{
    class Player{
        private:
            string name;
            stack<CardPtr> cards;
            stack<CardPtr> takenCards; 
            int wins;
            int losses; 
            int ties;
            int normal;

        public:
            Player(string name);
            ~Player();
            Player(Player const &) = delete;
            Player(Player &&) = delete;
            Player& operator=(Player const &) = delete;
            Player& operator=(Player &&) = delete;
            int stacksize();
            int cardesTaken();

            void clearDeck();
            void addCard(CardPtr card);
            void takeCard(CardPtr card);
            CardPtr getTopCard();
            string getName();

            double getWinrate();
            double getDrawrate();

            int getWins();
            int getLosses();
            int getTies();
            int getNormal();
            void winsInc();
            void lossesInc();
            void tiesInc();
            void normalInc();
    };
}
#endif