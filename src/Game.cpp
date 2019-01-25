#include "Game.hpp"
#include <iterator>

void Game::printPlayers() const {
    for(const auto i : m_players){
        std::cerr << "Player " << i->getName() << std::endl;
    }
}

void Game::movePlayer(Player *player, int steps) {
	m_board->getSpaces().at(player->get_pos())->removePlayer(player->getId());
	
	player->set_pos((player->get_pos() + steps) % 40);

	m_board->getSpaces().at(player->get_pos())->addPlayer(player->getId());
}

void Game::moveToPos(Player *player, int pos) {
	m_board->getSpaces().at(player->get_pos())->removePlayer(player->getId());

	player->set_pos(pos);

	m_board->getSpaces().at(player->get_pos())->addPlayer(player->getId());
}

void Game::send_to_jail(Player *player) {
	m_board->getSpaces().at(player->get_pos())->removePlayer(player->getId());

	player->send_to_jail();
	player->set_num_turns(1);

	m_board->getSpaces().at(player->get_pos())->addPlayer(player->getId());
}

void Game::release_from_jail(Player *player) {
	player->release_from_jail();
}

void Game::give_jail_card(Player *player) {
	player->receive_jail_card();
}

//std::pair<int , int> Game::throwDice() {
void Game::throwDice() {
	std::pair<int, int> num = std::make_pair(rand()%6+1, rand()%6+1);
	setDice(num.first, num.second);
    //return num;
}

bool Game::isAffordable(Player* player, Space* space)
{
	return player->balance().first > space->getBuyPrice();
}

bool Game::buildingAllowed(Player* player, Space* space){
    if(space->getType() != "PROPERTY")
        return false;
    std::vector<Space*> groupSpaces = m_board->getSpacesByGroup(space->getGroup());
    for(const auto i : groupSpaces){
        if(i->getOwner() != player->getId() || space->getNumBuildings() - i->getNumBuildings() >= 1
                || static_cast<Property*>(space)->getHousePrice() > player->get_wallet())
            return false;
    }
    return true;
}

// NOTE: We are relying on proper usage : this function won't be called unless
// player owns all properties in particular group and has houses on them
bool Game::sellingHouseAllowed(Space* space){
    std::vector<Space*> groupSpaces = m_board->getSpacesByGroup(space->getGroup());
    for(const auto i : groupSpaces){
        if(i->getNumBuildings() - space->getNumBuildings() >= 1 || space->getNumBuildings() == 0)
            return false;
    }
    return true;
}

//NOTE: Only current player will build because there is no game server at this point
void Game::build(Player* player, Space* property) {
	if (property->getType() != "PROPERTY") {
		return;
	}
    if(property->getOwner() == player->getId()){
        
        if(buildingAllowed(player, property)){
            //Ask for a normal house
            if(property->getNumBuildings() < 4){
                int availableHouses = m_bank->getHouses();
                if(availableHouses > 0){ //if there is enough houses in the bank
                    m_bank->setHouses(availableHouses-1);
                    property->setNumBuildings(property->getNumBuildings()+1);
                    m_bank->takeMoney(player, static_cast<Property*>(property)->getHousePrice());
                }else{
                    qDebug() << "Not enough houses";
                }
            
            }
            //Ask for a hotel
            else if(property->getNumBuildings() == 4){
                int availableHotels = m_bank->getHotels();
                if(m_bank->getHotels() > 0){
                    //if there is enough houses in the bank    
                    m_bank->setHotels(availableHotels-1);
                    property->setNumBuildings(property->getNumBuildings()+1);
                    m_bank->takeMoney(player, static_cast<Property*>(property)->getHousePrice());
                }else{
                    qDebug() << "Not enough hotels";
                }
                
            }else return;
        }
        
    }
}

double Game::pay_rent(Space* s)
{

    //TODO: prettify me later
    if(s->isOnMortgage())
        return -1;

	double amount = 0;
	std::pair<int, int> d = getDice();
	int dice = d.first + d.second;
    Player* curr_player = getCurrentPlayer();
	std::vector<Player*> players = getPlayers();

    // Get player which recieves rent
    Player* player = players.at(s->getOwner()-1);

	std::string type = s->getType();
	if (type == "PROPERTY")
	{

		amount = s->getRentPrice();
		if(player->check_properties(s))
			amount *= 2;
		else if(s->getNumBuildings() == 1)
			amount = s->getH1Price();
		else if(s->getNumBuildings() == 2)
			amount = s->getH2Price();
		else if(s->getNumBuildings() == 3)
			amount = s->getH3Price();
		else if(s->getNumBuildings() == 4)
			amount = s->getH4Price();
		else if(s->getNumBuildings() == 5)
			amount = s->getH5Price();

	}
	else if (type == "UTILITY")
	{

		bool both_utilities = player->check_utilities();
		if(!both_utilities)
			amount = dice * 4;
		else
			amount = dice * 10;

	}
	else if (type == "RAILROAD")
	{

		int num_railroads = player->check_railroads();
		
		amount = s->getRentPrice();
		if(num_railroads == 2)
			amount *= 2;
		else if(num_railroads == 3)
			amount *= 4;
		else if(num_railroads == 4)
			amount *= 8;

	}

    double player_balance = curr_player->balance().second;

	if(amount > player_balance)
	{
		std::cout << "BANKRUPCY" << std::endl;
		player->receive(player_balance);
	
		std::vector<Property*> props = curr_player->get_properties();
		unsigned prop_size = props.size();
		for(unsigned i=0; i<prop_size; i++)
			props[i]->setOwner(player->getId());
		
		std::vector<Utility*> utils = curr_player->get_utilities();
		unsigned util_size = utils.size();
		for(unsigned i=0; i<util_size; i++)
			utils[i]->setOwner(player->getId());
		
		std::vector<Railroad*> rails = curr_player->get_railroads();
		unsigned rail_size = rails.size();
		for(unsigned i=0; i<rail_size; i++)
			rails[i]->setOwner(player->getId());
		
		curr_player->set_bankrupt();
		
		Player* pTemp = curr_player;
		curr_player = m_players.at(curr_player->getId());
		delete pTemp;
		return amount;
    }

    curr_player->pay(amount);
	player->receive(amount);


    return amount;
}

//FIXME:
void Game::nextPlayer() {
    auto iter = std::find_if(m_players.begin(), m_players.end(), [&] (Player *p) { return p->getId() == m_current_player->getId(); });
    auto index = std::distance(m_players.begin(), iter);

    m_current_player = m_players.at((index+1)%m_players.size());
}

Player* Game::getCurrentPlayer() const {
    return m_current_player;
}

void Game::showBoard() const {
       Game::m_board->printBoard();
    }

std::vector<Player*> Game::getPlayers() const {
    return m_players;
}

Space* Game::getCurrentPlayerSpace() const {
    return m_board->getSpaces().at(m_current_player->get_pos());
}

Game::Game(std::vector<Player*> players, Board* board, Bank* bank){
    m_players = players;
    m_current_player = m_players.front();

    m_board = board;

    m_bank = bank;

    m_numOfPlayers = m_players.size();

	std::for_each(m_players.cbegin(), m_players.cend(), 
					[this] (const Player* p) { m_board->getSpaces().at(p->get_pos())->addPlayer(p->getId()); });
}

Game::Game(std::vector<std::string> player_names) {
    // Init players
    std::vector<Player*> players = Player::initializePlayers(player_names);
	unsigned i = 0;
	for(i=0; i < players.size(); i++)
		players[i]->init_wallet();
    std::copy(players.cbegin(), players.cend(), std::back_inserter(m_players));
    
    // Set first player
    m_current_player = m_players.front();
        
    // Create board
    m_board = new Board();
    
    // Create Bank
    m_bank = new Bank();

    m_numOfPlayers = m_players.size();

	std::for_each(m_players.cbegin(), m_players.cend(), 
					[this] (const Player* p) { m_board->getSpaces().at(p->get_pos())->addPlayer(p->getId()); });
}

Game::~Game()
{
	delete m_bank;
	delete m_board;
}
