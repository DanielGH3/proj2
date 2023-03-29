#include <string>
using namespace std;

#ifndef CARD_
#define CARD_
namespace ariel{
    class Card
    {
        private:
            int value;
            string symbol;
        public:
            Card(int value, string symbol);
            int getValue();
            string getSymbol();
    };
    
    typedef Card* CardPtr;
}
#endif