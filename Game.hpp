#pragma once 

#include "Board.hpp"
#include "Player.hpp"
#include <algorithm>
#include <vector>

class Game{
    
public:
    Game(int numPlayers);
    //f-je:
    // bacanje kockica
    // promena poteza
    //numplayers se zadaje iz maina(ako se stigne iz menija), bice argument konstruktora
    //u mainu ce biti i podaci o igracima
    void showBoard() const{
        m_board->printBoard();
    }
    
    void printPlayers() const;
    
private:
    //tabla, igraci, banka, aukcijska kuca, trenutno na potezu igrac
    Board* m_board;
    std::vector<Player*> m_players;
    //AuctionHouse m_auctionHouse;
    
};
