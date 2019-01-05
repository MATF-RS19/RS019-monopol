#include "Player.hpp"

//TODO: incorporate in qt (ako ostane vremena) neka za sada bude arg kom linije
std::vector<Player*> Player::initializePlayers(int numPlayers){
    
    std::vector<Player*> players;
    Player* p;
    std::string name;
    while(numPlayers){
        p = new Player();
        std::cout << "Enter your name: " << std::endl;
        std::cin >> name;
        p->set_name(name);
        p->set_pos(0);
        numPlayers--;
        players.push_back(p);
    }
    
    return players;
}

int Player::m_obj_count;

Player::Player()
{
    //TODO: implement me, mada ja mislim da nije potreban konstruktor bez argumenata
    m_id = m_obj_count;
}

Player::~Player()
{
	m_obj_count--;
}

bool Player::is_in_jail() const
{
	return m_in_jail;
}

void Player::send_to_jail()
{
	if (m_in_jail == true) return;

	m_in_jail = true;
}

void Player::release_from_jail()
{
	if (m_in_jail == false) return;

	m_in_jail = false;
}

int Player::balance() const
{
	return m_wallet;
}

void Player::pay(int amount)
{
	m_wallet -= amount;
}

void Player::buy(Space* space)
{
	// promeniti u upozorenje
	int price = space->getBuyPrice();
	if (balance() < price)
	{
		std::cout << "Not enough money." << std::endl;
		return;
	}
	else
	{
		pay(price);
		std::string type = space->getType();
		if (type == "PROPERTY")
		{
			add_property((Property*)space);
		}
		else if (type == "UTILITY")
		{
			add_utility((Utility*)space);
		}
		else if (type == "RAILROAD")
		{
			add_railroad((Railroad*)space);
		}
		add_space(space);
		space->setOwned();
	}
	
	return;
}

void Player::pay_rent(Space* space, Player* player, int dice)
{
	double amount = 0;
	
	std::string type = space->getType();
	if (type == "PROPERTY")
	{
		Property* p = (Property*)space;
		amount = p->getRentPrice();
		if(check_properties(p, player))
			amount *= 2;
	}
	else if (type == "UTILITY")
	{
		bool both_utilities = check_utilities(player);
		if(!both_utilities)
			amount = dice * 4;
		else
			amount = dice * 10;
	}
	else if (type == "RAILROAD")
	{
		Railroad* r = (Railroad*)space;
		int num_railroads = check_railroads(player);
		
		amount = r->getRentPrice();
		if(num_railroads == 2)
			amount *= 2;
		else if(num_railroads == 3)
			amount *= 4;
		else if(num_railroads == 4)
			amount *= 8;
	}
	
	pay(amount);
	player->receive(amount);
	
	return;
}

void Player::receive(int amount)
{
	m_wallet += amount;
}

//NOTE: uncomment later
// const Player::Coordinate& position() const
// {
// 	return m_pos;
// }

// Coordinate& Player::position() const
// {
// 	return m_pos;
// }

//getPosition -> space na kome se nalazi
//setPosition -> 

// TODO: void move(int i) -> pokrece se i polja po tabli => treba neko ko ima pristup tabli da pomera (Game)
// TODO: void build(std::string building)

void Player::set_name(std::string name)
{
	m_name = name;
}

std::string Player::get_name() const{
    return m_name;
}

void Player::set_pos(int pos){
    m_pos = pos;
}

int Player::get_pos() const{
    return m_pos;
}

void Player::add_property(Property* p){
    owned_properties.push_back(p);
}

void Player::add_utility(Utility* u){
    owned_utilities.push_back(u);
}

void Player::add_railroad(Railroad* r){
    owned_railroads.push_back(r);
}

std::vector<Railroad*> Player::get_railroads() const{
    return owned_railroads;
}

std::vector<Utility*> Player::get_utilities() const{
    return owned_utilities;
}

std::vector<Property*> Player::get_properties() const{
    return owned_properties;
}

std::vector<Space*> Player::get_spaces() const{
    return owned_spaces;
}

void Player::add_space(Space* s){
    owned_spaces.push_back(s);
}

bool Player::check_properties(Property* p, Player* player)
{
	std::vector<Property*> my_properties = player->get_properties();		
	std::string colour = p->getColour();
	int count = 0;
	unsigned i = 0;
	bool has_all = false;
	if(colour == "D_BLUE" || colour == "L_BLUE")
		count = 1;
	for(; i < my_properties.size(); i++)
	{
		if(my_properties[i]->getColour() == colour)
			count ++;
	}		
	
	if(count == 3)
		has_all = true;
	
	return has_all;
}

bool Player::check_utilities(Player* player)
{
	bool has_all = false;
	std::vector<Utility*> my_utilities = player->get_utilities();
	if(my_utilities.size() == 2)
		has_all = true;
	return has_all;
}

int Player::check_railroads(Player* player)
{
	std::vector<Railroad*> my_railroads = player->get_railroads();
	return my_railroads.size();
}
