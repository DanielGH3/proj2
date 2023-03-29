#include "player.hpp"

#ifndef GAME_
#define GAME_
namespace ariel{
    class Game{
        private:
            Player* p1;
            Player* p2;
            string turns;
            string lasturn;
            void addToLastTurn(CardPtr card1, CardPtr card2);
        public:
            Game(Player& player1, Player& player2);
            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();

            void playAgain();
    };
}
#endif