#pragma once

#include <algorithm>
#include <vector>

#include <typeinfo>
#include <iostream>

#include "/home/aleksandar/RS019-monopol/Space.hpp"
#include "/home/aleksandar/RS019-monopol/Utility.hpp"
#include "/home/aleksandar/RS019-monopol/Railroad.hpp"
#include "/home/aleksandar/RS019-monopol/ActionSpace.hpp"
#include "/home/aleksandar/RS019-monopol/Card.hpp"
#include "/home/aleksandar/RS019-monopol/Property.hpp"

class Board{

	public:
		Board();

        Card drawCard();
        
        std::vector<Space*> getSpaces() const;
        
        std::vector<Card*> getChanceDeck() const;
        
        std::vector<Card*> getCommunityChestDeck() const;

	void printBoard() const;
        
		~Board();

	private:
		
		std::vector<Space*> m_spaces; 
		std::vector<Card*> m_chanceDeck;
		std::vector<Card*> m_communityChestDeck;
};


