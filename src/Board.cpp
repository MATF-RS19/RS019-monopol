#include "Board.hpp"

#define NUM_CARDS 17

void Board::printBoard() const {
    for(const auto i : m_spaces) {
        i->printSpace();
    }
}

std::vector<Space*> Board::getSpaces() const{
    return m_spaces;
}

Card Board::drawChanceCard() {
    Card result = *m_chanceDeck.at(0);
    m_chanceDeck.erase(m_chanceDeck.begin());
    //TODO: if not jail card put back, else add the card to player
    //TODO: remove magic nums
    if(result.getAction() != 7){
        m_chanceDeck.push_back(&result);
    }
    return result;
}

Card Board::drawCommunityCard() {
    Card result = *m_communityChestDeck.at(0);
    m_communityChestDeck.erase(m_communityChestDeck.begin());
    //TODO: if not jail card put back, else add the card to player
    //TODO: remove magic nums
    if(result.getAction() != 21){
        m_communityChestDeck.push_back(&result);
    }
    return result;
}

void Board::setSpace(int index, Space* space){
    m_spaces.at(index) = space;
}

Board::Board() {
    std::vector<Utility*> utils = Utility::initialize_utilities();
	std::vector<Railroad*> rails = Railroad::initialize_railroads();
	std::vector<Card*> cardDeck = Card::initialize_cards();
	std::vector<Property*> properties = Property::initialize_properties();
    
	//0 
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::GO)));
	// 1
	m_spaces.push_back(properties.at(0));
	// 2
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
	// 3
	m_spaces.push_back(properties.at(1));
	// 4
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::INCOME_TAX)));
	// 5
	m_spaces.push_back(rails.at(0)); //reading 
	// 6
	m_spaces.push_back(properties.at(2));
	// 7
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
	// 8
	m_spaces.push_back(properties.at(3));
	// 9
	m_spaces.push_back(properties.at(4));
	// 10
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::JAIL)));
	// 11
	m_spaces.push_back(properties.at(5));
	// 12
	m_spaces.push_back(utils.at(1)); // electric company
	// 13
	m_spaces.push_back(properties.at(6));
	// 14
	m_spaces.push_back(properties.at(7));
	// 15
	m_spaces.push_back(rails.at(1)); //penn
	// 16
	m_spaces.push_back(properties.at(8));
	// 17
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
	// 18
	m_spaces.push_back(properties.at(9));
	// 19
	m_spaces.push_back(properties.at(10));
	// 20
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::FREE_PARKING)));
	// 21
	m_spaces.push_back(properties.at(11));
	// 22
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
	// 23
	m_spaces.push_back(properties.at(12));
	// 24
	m_spaces.push_back(properties.at(13));
	// 25
	m_spaces.push_back(rails.at(2)); //bo
	// 26
	m_spaces.push_back(properties.at(14));
	// 27
	m_spaces.push_back(properties.at(15));
	// 28
	m_spaces.push_back(utils.at(0)); // water works
	// 29
	m_spaces.push_back(properties.at(16));
	// 30
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::GOTO_JAIL)));
	// 31
	m_spaces.push_back(properties.at(17));
	// 32
	m_spaces.push_back(properties.at(18));
	// 33
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)));
	// 34
	m_spaces.push_back(properties.at(19));
	// 35
	m_spaces.push_back(rails.at(3)); //sl
	// 36
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)));
	// 37
	m_spaces.push_back(properties.at(20));
	// 38
	m_spaces.push_back(new ActionSpace(static_cast<int>(ActionSpace::EnumActionSpace::LUXURY_TAX)));
	// 39
	m_spaces.push_back(properties.at(21));

    //TODO: put me in a func?
    //Shuffle card decks
	std::copy(cardDeck.cbegin(), cardDeck.cbegin() + NUM_CARDS, std::back_inserter(m_chanceDeck));
	std::random_shuffle(m_chanceDeck.begin(), m_chanceDeck.end());

	std::copy(cardDeck.cbegin() + NUM_CARDS, cardDeck.cend(), std::back_inserter(m_communityChestDeck));
	std::random_shuffle(m_communityChestDeck.begin(), m_communityChestDeck.end());
}	

std::vector<Space*> Board::getSpacesByGroup(std::string group) const {
    std::vector<Space*> result;
    std::copy_if(m_spaces.cbegin(), m_spaces.cend(), std::back_inserter(result),
                 [group](Space* g){ return !strcmp(g->getGroup().c_str(),group.c_str()); }
    );
    return result;
}

Board::~Board() {
}
