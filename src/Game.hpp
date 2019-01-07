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
    
    void printPlayers() const;
    
    Player* getCurrentPlayer() const;
    
    Space* getCurrentPlayerSpace() const;
    
    void nextPlayer();
    
    void build(Player* player, Property* property);
	void pay_rent(Space* space, Player* player);
    
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
    
private:
    //tabla, igraci, banka, aukcijska kuca, trenutno na potezu igrac
    Board* m_board;
    std::vector<Player*> m_players;
    Player* m_current_player;
    Bank* m_bank;
    int _dice;
};
