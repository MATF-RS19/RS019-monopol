#pragma once 

#include "Board.hpp"
#include "Player.hpp"
#include "Bank.hpp"
#include <algorithm>
#include <vector>

class Game{
    
public:
    Game(int numPlayers);
    //f-je:
    // pokretanje igre + petlja
    //numplayers se zadaje iz maina(ako se stigne iz menija), bice argument konstruktora
    //u mainu ce biti i podaci o igracima
//     void startGame();
    
    std::pair<int, int> throwDice();
    
    std::vector<Player*> getPlayers() const;
    
    void showBoard() const;
    
    void printPlayers() const;
    
    Player* getCurrentPlayer() const;
    
    Space* getCurrentPlayerSpace() const;
    
    void nextPlayer();
    
    //void sellToCurrentPlayer();
    
    void build(Player* player, Property* property);
    
    void movePlayer(Player *player, int steps);
    
    
    //TODO: remove me, i don't need to exist
    Bank* getBank() const{
        return m_bank;
    }
    //TODO: remove me
    Board* getBoard() const{
        return m_board;
    }
    
private:
    //tabla, igraci, banka, aukcijska kuca, trenutno na potezu igrac
    Board* m_board;
    std::vector<Player*> m_players;
    Player* m_current_player;
    Bank* m_bank;
    
};
