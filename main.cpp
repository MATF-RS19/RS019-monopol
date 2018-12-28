#include <vector>

//TODO: remove these 
#include "Card.hpp"
#include "Property.hpp"
#include "Utility.hpp"
#include "Railroad.hpp"
//
#include "Board.hpp"
#include <iostream>
#include <ctime>

#define NUM_PROPERTY 50
#define NUM_UTILITY 2
#define NUM_RAILROAD 4

// using namespace std;

std::vector<Property*> initialize_properties();

int main(int argc, char** argv)
{
    std::srand(unsigned(std::time(0)));
    
    Board *b = new Board();
    
    Card dummyCard = b->drawCard();
    
    std::cout << dummyCard.getMsg() << std::endl;
 	
	return 0;
}



std::vector<Property*> initialize_properties()
{
	std::vector<Property*> properties(NUM_PROPERTY);
	return properties;
}




