#include "Board.hpp"

#define NUM_CARDS 17

void Board::printBoard() const{
    
    for(const auto i : m_spaces){
        i->printSpace();
    }
    
}

std::vector<Space*> Board::getSpaces() const{
    
    return m_spaces;
    
}

Card Board::drawCard(){
    
    Card result = *m_chanceDeck.at(0);
    m_chanceDeck.erase(m_chanceDeck.begin());
    //TODO: if not jail card put back, else add the card to player
    //TODO: remove magic nums
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
	std::vector<Property*> properties = Property::initialize_properties();
    
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::GO))); 
	m_spaces.push_back(properties.at(0));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
	m_spaces.push_back(properties.at(1));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::INCOME_TAX)));
	m_spaces.push_back(rails.at(0)); //reading 
	m_spaces.push_back(properties.at(2));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
	m_spaces.push_back(properties.at(3));
	m_spaces.push_back(properties.at(4));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::JAIL)));
	m_spaces.push_back(properties.at(5));
	m_spaces.push_back(utils.at(1)); // electric company
	m_spaces.push_back(properties.at(6));
	m_spaces.push_back(properties.at(7));
	m_spaces.push_back(rails.at(1)); //penn
	m_spaces.push_back(properties.at(8));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
	m_spaces.push_back(properties.at(9));
	m_spaces.push_back(properties.at(10));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::FREE_PARKING)));
	m_spaces.push_back(properties.at(11));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
	m_spaces.push_back(properties.at(12));
	m_spaces.push_back(properties.at(13));
	m_spaces.push_back(rails.at(2)); //bo
	m_spaces.push_back(properties.at(14));
	m_spaces.push_back(properties.at(15));
	m_spaces.push_back(rails.at(0)); // water works
	m_spaces.push_back(properties.at(16));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::GOTO_JAIL)));
	m_spaces.push_back(properties.at(17));
	m_spaces.push_back(properties.at(18));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
	m_spaces.push_back(properties.at(19));
	m_spaces.push_back(rails.at(3)); //sl
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
	m_spaces.push_back(properties.at(20));
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::LUXURY_TAX)));
	m_spaces.push_back(properties.at(21));

    //TODO: put me in a func?
    //Shuffle card decks
	std::copy(cardDeck.cbegin(), cardDeck.cbegin() + NUM_CARDS, std::back_inserter(m_chanceDeck));
	std::random_shuffle(m_chanceDeck.begin(), m_chanceDeck.end());

	std::copy(cardDeck.cbegin() + NUM_CARDS, cardDeck.cend(), std::back_inserter(m_communityChestDeck));
	std::random_shuffle(m_communityChestDeck.begin(), m_communityChestDeck.end());

}	

Board::~Board(){
    std::cout << "Destroying board" << std::endl;
}
