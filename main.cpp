#include <vector>
#include <iostream>
#include <ctime>

#include "Board.hpp"

int main(int argc, char** argv)
{
    std::srand(unsigned(std::time(0)));
    
    Board *b = new Board();
    
    Card dummyCard = b->drawCard();
    
    std::cout << dummyCard.getMsg() << std::endl;
 	
	return 0;
}





