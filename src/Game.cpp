#include "Game.hpp"

void Game::printPlayers() const{
    for(const auto i : m_players){
        std::cerr << "Player " << i->get_name() << std::endl;
    }
}

void Game::movePlayer(Player *player, int steps){
    player->set_pos((player->get_pos() + steps) % 40);
}

std::pair<int , int> Game::throwDice(){
	std::pair<int, int> num = std::make_pair(rand()%6+1, rand()%6+1);
	setDice(num.first + num.second);
    return num;
}

//NOTE: Only current player will build because game is turn based at this point
//      
void Game::build(Player* player, Property* property){
    
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

void Game::pay_rent(Space* space, Player* player)
{
	double amount = 0;
	int dice = getDice();
	
	std::string type = space->getType();
	if (type == "PROPERTY")
	{
		Property* p = (Property*)space;
		amount = p->getRentPrice();
		if(player->check_properties(p) && p->getNumBuildings() == 0)
			amount *= 2;
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
	
	player->pay(amount);
	player->receive(amount);
	
	return;
}

void Game::nextPlayer(){
    Player* p = m_players.front();
    m_players.erase(m_players.begin());
    m_players.push_back(p);
    m_current_player = m_players.at(0);
}

Player* Game::getCurrentPlayer() const{
    return m_current_player;
}

void Game::showBoard() const{
        m_board->printBoard();
    }

std::vector<Player*> Game::getPlayers() const{
    return m_players;
}

Space* Game::getCurrentPlayerSpace() const{
    return m_board->getSpaces().at(m_current_player->get_pos());
}

Game::Game(int numPlayers){
    
    // Init players
    std::vector<Player*> players = Player::initializePlayers(numPlayers);
    std::copy(players.cbegin(), players.cend(), std::back_inserter(m_players));
    
    // Set first player
    m_current_player = m_players.front();
        
    // Create board
    m_board = new Board();
    
    // Create Bank
    m_bank = new Bank();
    
}
