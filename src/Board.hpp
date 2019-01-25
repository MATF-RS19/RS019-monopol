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
#include <cstring>

class Board {
	public:
		Board();
        
        std::vector<Space*> getSpaces() const;
        
        std::vector<Card*> getChanceDeck() const;
        
        std::vector<Card*> getCommunityChestDeck() const;

        Card drawCommunityCard();

        Card drawChanceCard();

        void printBoard() const;

        void setSpace(int index, Space* space);
        
        std::vector<Space*> getSpacesByGroup(std::string group) const;
        
		~Board();

	private:
		
		std::vector<Space*> m_spaces; 
		std::vector<Card*> m_chanceDeck;
		std::vector<Card*> m_communityChestDeck;
};


