#include "Game.hpp"

void Game::printPlayers() const {
    for(const auto i : m_players){
        std::cerr << "Player " << i->get_name() << std::endl;
    }
}

void Game::movePlayer(Player *player, int steps) {
    player->set_pos((player->get_pos() + steps) % 40);
}

std::pair<int , int> Game::throwDice() {
	std::pair<int, int> num = std::make_pair(rand()%6+1, rand()%6+1);
	setDice(num.first + num.second);
    return num;
}

//NOTE: Only current player will build because game is turn based at this point
//      
void Game::build(Player* player, Space* property) {
	if (property->getType() != "PROPERTY") {
		std::cerr << "Space is not upgradeable\n" << std::endl;
		return;
	}
    if(property->getOwner() == player->getId()){
        // Check if player has purchased all properties in a particular group and
        // if building order is valid
        std::vector<Space*> group = m_board->getSpacesByGroup(property->getGroup());
        bool valid = true;
        for(auto i: group){
            if(i->getOwner() != player->getId() || (abs(property->getNumBuildings() - i->getNumBuildings() + 1) > 1)){
                std::cerr << "Building not allowed" << std::endl;
                valid = false;
                break;
            }
        }
        
        if(valid){
            //Ask for a normal house
            if(property->getNumBuildings() < 4){
                std::cerr << "Normal house\n";
                int availableHouses = m_bank->getHouses();
                std::cerr << "availableHouses" << availableHouses << std::endl;
                if(availableHouses > 0){ //if there is enough houses in the bank
                    m_bank->setHouses(availableHouses-1);
                    property->setNumBuildings(property->getNumBuildings()+1);
                }else{
                    std::cerr << "Not enough houses\n";
                }
            
            }
            //Ask for a hotel
            else if(property->getNumBuildings() == 4){
                std::cerr << "Hotel\n";
                int availableHotels = m_bank->getHotels();
                if(m_bank->getHotels() > 0){
                    //if there is enough houses in the bank
                    
                    m_bank->setHotels(availableHotels-1);
                    property->setNumBuildings(property->getNumBuildings()+1);
                }else{
                    std::cerr << "Not enough hotels\n";
                }
                
            }else return;
        }
        
    }
}


double Game::pay_rent(Space* space)
{
	double amount = 0;
	int dice = getDice();
    Player* curr_player = getCurrentPlayer();
    Player* player = getPlayers().at(space->getOwner());
	
	std::string type = space->getType();
	if (type == "PROPERTY")
	{
		Property* p = (Property*)space;
		amount = p->getRentPrice();
		if(player->check_properties(p))
			amount *= 2;
		else if(p->getNumBuildings() == 1)
			amount = p->getH1Price();
		else if(p->getNumBuildings() == 2)
			amount = p->getH2Price();
		else if(p->getNumBuildings() == 3)
			amount = p->getH3Price();
		else if(p->getNumBuildings() == 4)
			amount = p->getH4Price();
		else if(p->getNumBuildings() == 5)
			amount = p->getH5Price();
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
		Railroad* r = (Railroad*)space;
		int num_railroads = player->check_railroads();
		
		amount = r->getRentPrice();
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
		
		//TODO: destroy current player
		return amount;
	}
	
    curr_player->pay(amount);
	player->receive(amount);

    return amount;
}

void Game::nextPlayer() {
    Player* p = m_players.front();
    m_players.erase(m_players.begin());
    m_players.push_back(p);
    m_current_player = m_players.at(0);
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

Game::Game(int numPlayers, std::vector<std::string> player_names) {
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
}
