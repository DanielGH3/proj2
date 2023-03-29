#include "doctest.h"
#include <player.hpp>
#include <game.hpp>
#include <card.hpp>

using namespace ariel;

TEST_CASE("1.getWins()/getLosses() count correctly") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2); 
    game.playAll();
    game.playAgain();
    game.playAll();
    CHECK(p1.getWins() + p2.getWins() + p1.getLosses() + p2.getLosses() == 4);
}

TEST_CASE("2.Player winrate correctly") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2); 
    game.playAll();
    game.playAgain();
    game.playAll();
    int wins = p1.getWins();
    int losses = p1.getLosses();
    double winrate = (double)wins / (wins + losses);
    CHECK(winrate == p1.getWinrate());
}

TEST_CASE("3.Names as stored as expected") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Daniel");
    Player p4("John Doe");
    CHECK(p1.getName() == "Alice");
    CHECK(p2.getName() == "Bob");
    CHECK(p3.getName() == "Daniel");
    CHECK(p4.getName() == "John Doe");
}

TEST_CASE("4.Player drawrate correctly") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2); 
    game.playAll();
    game.playAgain();
    game.playAll();
    int draws = p1.getTies();
    int normals = p1.getNormal();
    double drawrate = (double)draws / (draws + normals);
    CHECK(drawrate == p1.getDrawrate());
}

TEST_CASE("5.Player init correctly") {
    Player p1("Alice");
    CHECK(p1.getName() == "Alice");
    CHECK(p1.getDrawrate() == 0);
    CHECK(p1.getWinrate() == 0);
    CHECK(p1.getWins() == 0);
    CHECK(p1.getLosses() == 0);
    CHECK(p1.getTies() == 0);
    CHECK(p1.getNormal() == 0);
}

TEST_CASE("6.Win loss count follows diffrect games") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2); 
    game.playAll();
    Game anothergame(p1, p2); 
    game.playAll();

    CHECK(p1.getWins() + p2.getWins() + p1.getLosses() + p2.getLosses() == 4);
}

TEST_CASE("7.Cards init correctly") {
    CardPtr c = new Card(1, "diamond");
    CHECK(c->getValue() == 1);
    CHECK(c->getSymbol() == "diamond");
    delete c;
}

TEST_CASE("8.Player stack size") {
    Player p1("Alice");
    CardPtr c1 = new Card(1, "diamond");
    CardPtr c2 = new Card(2, "diamond");
    CHECK(p1.stacksize() == 0);
    p1.addCard(c1);
    CHECK(p1.stacksize() == 1);
    p1.addCard(c2);
    CHECK(p1.stacksize() == 2);
}

TEST_CASE("9.Player remove all from stack") {
    Player p1("Alice");
    CardPtr c1 = new Card(1, "diamond");
    CardPtr c2 = new Card(2, "diamond");
    CardPtr c3 = new Card(3, "diamond");
    p1.addCard(c1);
    p1.addCard(c2);
    p1.addCard(c3);
    CHECK(p1.stacksize() == 3);
    p1.clearDeck();
    CHECK(p1.stacksize() == 0);
    delete c1;
    delete c2;
    delete c3;
}

TEST_CASE("10.Player add vs take") {
    Player p1("Alice");
    CardPtr c1 = new Card(1, "diamond");
    CardPtr c2 = new Card(2, "diamond");
    CardPtr c3 = new Card(3, "diamond");
    p1.addCard(c1);
    p1.addCard(c2);
    p1.addCard(c3);
    CHECK(p1.stacksize() == 3);
    CHECK(p1.cardesTaken() == 0);
}

TEST_CASE("11.Player take card") {
    Player p1("Alice");
    CardPtr c1 = new Card(1, "diamond");
    CardPtr c2 = new Card(2, "diamond");
    CardPtr c3 = new Card(3, "diamond");
    p1.takeCard(c1);
    p1.takeCard(c2);
    p1.takeCard(c3);
    CHECK(p1.cardesTaken() == 3);
}

TEST_CASE("12.Player top card correct orded") {
    Player p1("Alice");
    CardPtr c1 = new Card(1, "diamond");
    CardPtr c2 = new Card(10, "diamond");
    CardPtr c3 = new Card(13, "diamond");
    p1.addCard(c1);
    p1.addCard(c2);
    p1.addCard(c3);

    CardPtr c = p1.getTopCard();
    CHECK(c->getValue() == 13);
    c = p1.getTopCard();    
    CHECK(c->getValue() == 10);
    c = p1.getTopCard();
    CHECK(c->getValue() == 1);
    delete c1; 
    delete c2;
    delete c3;
}

TEST_CASE("13.Cards add up deck size") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2); 
    game.playAll();
    game.playAgain();
    game.playAll();
    CHECK(p1.cardesTaken() + p2.cardesTaken() == 104);
}

TEST_CASE("14.Removing cards count") {
    Player p1("Alice");
    CardPtr c1 = new Card(1, "diamond");
    CardPtr c2 = new Card(2, "diamond");
    CardPtr c3 = new Card(3, "diamond");
    p1.addCard(c1);
    p1.addCard(c2);
    p1.addCard(c3);
    CHECK(p1.stacksize() == 3);
    p1.getTopCard();
    CHECK(p1.stacksize() == 2);
    p1.getTopCard();
    CHECK(p1.stacksize() == 1);
    p1.getTopCard();
    CHECK(p1.stacksize() == 0);
    delete c1;
    delete c2;
    delete c3;
}

TEST_CASE("15.Removing cards when empty") {
    Player p1("Alice");
    CardPtr c1 = new Card(1, "diamond");
    p1.addCard(c1);
    p1.getTopCard();
    CardPtr card = p1.getTopCard();    
    CHECK(card == NULL);
    delete c1;
    delete card;
}

TEST_CASE("16.Removing cards value") {
    Player p1("Alice");
    CardPtr c1 = new Card(10, "clubs");
    CardPtr c2 = new Card(2, "diamond");
    CardPtr c3 = new Card(3, "diamond");
    p1.addCard(c1);
    p1.addCard(c2);
    p1.addCard(c3);
    p1.getTopCard();
    p1.getTopCard();
    CardPtr card = p1.getTopCard();    
    CHECK(card->getValue() == 10);
    CHECK(card->getSymbol() == "clubs");
    delete c1;
    delete c2;
    delete c3;
}

TEST_CASE("17.Cards add up deck size v2") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2); 
    game.playAll();
    Game game1(p1, p2); 
    game1.playAll();
    CHECK(p1.cardesTaken() + p2.cardesTaken() == 104);
}

TEST_CASE("18.Win/loss counting works with more players") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("daniel");
    Game game1(p1, p2); 
    game1.playAll();   
    Game game2(p2, p3); 
    game2.playAll();
    CHECK(p1.getWins() + p1.getLosses() + p2.getWins() + p2.getLosses() + p3.getWins() + p3.getLosses() == 4);
}

TEST_CASE("19.Winrate works with more players") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("daniel");
    Game game1(p1, p2); 

    game1.playAll();
    int wins = p2.getWins();
    int losses = p2.getLosses();
    double winrate = (double)wins / (wins + losses);
    CHECK(winrate == p2.getWinrate());

    Game game2(p2, p3); 
    game2.playAll();
    wins = p2.getWins();
    losses = p2.getLosses();
    winrate = (double)wins / (wins + losses);
    CHECK(winrate == p2.getWinrate());
}

TEST_CASE("20.Card counting with more players") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("daniel");
    Player p4("dan");
    Game game1(p1, p2); 
    game1.playAll();

    Game game2(p2, p3); 
    game2.playAll();

    Game game3(p3, p4); 
    game3.playAll();

    int cards = p1.cardesTaken() + p2.cardesTaken() + p3.cardesTaken() + p4.cardesTaken();
    CHECK(cards == 156);
}