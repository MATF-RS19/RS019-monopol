#pragma once 

#include "Board.hpp"
#include "Player.hpp"
#include "Bank.hpp"
#include <algorithm>
#include <vector>

class Game {
public:
    Game(int numPlayers, std::vector<std::string> player_names);
    
    std::pair<int, int> throwDice();
    
    std::vector<Player*> getPlayers() const;
    
    void showBoard() const;
	Board* getBoard() {
		return m_board;
	}
    
    void printPlayers() const;
    
    Player* getCurrentPlayer() const;
    
    Space* getCurrentPlayerSpace() const;
    
    void nextPlayer();
    
    //TODO: implementirati u .cpp jer mora da moze da se pristupi i igracima i ostalim glupostima
    //switch(action) i onda za svaku od njih se gleda sta treba da se radi pomeranje igraca, placanje ostalima itd
    void executeCardAction(int action, Player* player);

    //Current player pays to the owner of the space
    double pay_rent(Space* space);
    void build(Player* player, Space* property);
    
    void movePlayer(Player *player, int steps);
    
    int getDice() {
		return _dice;
    }
    
    void setDice(int num) {
		_dice = num;
    }
    
    Bank* getBank() const {
	    return m_bank;
	}
	
	Board* getBoard() const {
	    return m_board;
	}
    
    std::pair<int,int> getMatrixAtPos(int pos){
        return posToMatrixMap.at(pos);
	} 
private:
    //tabla, igraci, banka, aukcijska kuca, trenutno na potezu igrac
    Board* m_board;
    std::vector<Player*> m_players;
    Player* m_current_player;
    Bank* m_bank;
    int _dice;
    const std::map<int, std::pair<int,int>> posToMatrixMap =
                                                          {{ 0, std::make_pair(10,10) },
                                                           { 1, std::make_pair(10,9) },
                                                           { 2, std::make_pair(10,8) },
                                                           { 3, std::make_pair(10,7) },
                                                           { 4, std::make_pair(10,6) },
                                                           { 5, std::make_pair(10,5) },
                                                           { 6, std::make_pair(10,4) },
                                                           { 7, std::make_pair(10,3) },
                                                           { 8, std::make_pair(10,2) },
                                                           { 9, std::make_pair(10,1) },
                                                           { 10,std::make_pair(10,0) },
                                                           { 11,std::make_pair(9,0) },
                                                           { 12,std::make_pair(8,0) },
                                                           { 13,std::make_pair(7,0) },
                                                           { 14,std::make_pair(6,0) },
                                                           { 15,std::make_pair(5,0) },
                                                           { 16,std::make_pair(4,0) },
                                                           { 17,std::make_pair(3,0) },
                                                           { 18,std::make_pair(2,0) },
                                                           { 19,std::make_pair(1,0) },
                                                           { 20,std::make_pair(0,0) },
                                                           { 21,std::make_pair(0,1) },
                                                           { 22,std::make_pair(0,2) },
                                                           { 23,std::make_pair(0,3) },
                                                           { 24,std::make_pair(0,4) },
                                                           { 25,std::make_pair(0,5) },
                                                           { 26,std::make_pair(0,6) },
                                                           { 27,std::make_pair(0,7) },
                                                           { 28,std::make_pair(0,8) },
                                                           { 29,std::make_pair(0,9) },
                                                           { 30,std::make_pair(0,10)},
                                                           { 31,std::make_pair(1,10) },
                                                           { 32,std::make_pair(2,10) },
                                                           { 33,std::make_pair(3,10) },
                                                           { 34,std::make_pair(4,10) },
                                                           { 35,std::make_pair(5,10) },
                                                           { 36,std::make_pair(6,10) },
                                                           { 37,std::make_pair(7,10) },
                                                           { 38,std::make_pair(8,10) },
                                                           { 39,std::make_pair(9,10) }};
};
