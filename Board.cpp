#include "Board.hpp"

Card Board::drawCard(){
    
    Card result = *m_chanceDeck.at(0);
    m_chanceDeck.erase(m_chanceDeck.begin());
    //TODO: if not jail card put back, else add the card to player
    if(result.getAction() != 7 && result.getAction() != 22){
        std::cout << "Puting card back" << std::endl;
        m_chanceDeck.push_back(&result);
    }
    return result;
}

Board::Board(){

	std::vector<Utility*> utils = Utility::initialize_utilities();

	std::vector<Railroad*> rails = Railroad::initialize_railroads();

	std::vector<Card*> cardDeck = Card::initialize_cards();
    
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::GO))); 
//	m_spaces[1] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
//	m_spaces[3] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::INCOME_TAX)));
	m_spaces.push_back(rails.at(0)); //reading 
//	m_spaces[6] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
//	m_spaces[8] = //property
//	m_spaces[9] = //property
//	m_spaces[10] = //JAIL
//	m_spaces[11] = //property
	m_spaces.push_back(utils.at(1)); // electric company
//	m_spaces[13] = //property
//	m_spaces[14] = //property
	m_spaces.push_back(rails.at(1)); //penn
//	m_spaces[16] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
//	m_spaces[18] = //property
//	m_spaces[19] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::FREE_PARKING)));
//	m_spaces[21] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
//	m_spaces[23] = //property
//	m_spaces[24] = //property
	m_spaces.push_back(rails.at(2)); //bo
//	m_spaces[26] = //property
//	m_spaces[27] = //property
	m_spaces.push_back(rails.at(0)); // water works
//	m_spaces[29] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
//	m_spaces[31] = //property
//	m_spaces[32] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
//	m_spaces[34] = //property
	m_spaces.push_back(rails.at(3)); //sl
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
//	m_spaces[37] = //property
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::LUXURY_TAX)));
//	m_spaces[39] = //property

	
	
    //TODO: remove magick numbers
	std::copy(cardDeck.cbegin(), cardDeck.cbegin() + 17, std::back_inserter(m_chanceDeck));
	std::random_shuffle(m_chanceDeck.begin(), m_chanceDeck.end());

	std::copy(cardDeck.cbegin() + 17, cardDeck.cend(), std::back_inserter(m_communityChestDeck));
	std::random_shuffle(m_communityChestDeck.begin(), m_communityChestDeck.end());
	
	


}	
