#pragma once

#include <algorithm>
#include <vector>

#include <typeinfo>
#include <iostream>

#include "Space.hpp"
#include "Utility.hpp"
#include "Railroad.hpp"
#include "ActionSpace.hpp" 
#include "Card.hpp"
#include "Property.hpp"

class Board{

	public:
		Board();

        Card drawCard();

	void printBoard() const;
        
		~Board();

	private:
		
		std::vector<Space*> m_spaces; 
		std::vector<Card*> m_chanceDeck;
		std::vector<Card*> m_communityChestDeck;
};


