#include <vector>
#include <iostream>
#include <ctime>

#include "Board.hpp"
#include "Game.hpp"

int main(int argc, char** argv)
{
    std::srand(unsigned(std::time(0)));
    
    // Game g;
    
    //NOTE: nije potrebna dinamicka alokacija, cak je i bolje da se ne brinemo o curenju memorije
    //Board *b = new Board();
    //Board b;
    
    //Card dummyCard = b.drawCard();
    
    //std::cout << dummyCard.getMsg() << std::endl;
 	
    //b.printBoard();
    
    Game g{4};
    g.showBoard();
    g.printPlayers();
    
	return 0;
}





