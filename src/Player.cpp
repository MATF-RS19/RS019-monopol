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
    m_obj_count++;
    m_id = m_obj_count;
}

Player::~Player()
{
	m_obj_count--;
}

int Player::getId() const{
    return m_id;
}

bool Player::is_in_jail() const
{
	return m_in_jail;
}

void Player::send_to_jail()
{
	if (m_in_jail == true) return;
	if (has_jail_card)
	{
		release_from_jail();
		has_jail_card = false;
		//TODO: staviti kartu nazad u spil
	}

	m_in_jail = true;
	num_turns_in_jail = 1;
}

void Player::release_from_jail()
{
	if (m_in_jail == false) return;

	m_in_jail = false;
	num_turns_in_jail = 0;
}

void Player::set_num_turns(int num)
{
	num_turns_in_jail = num;
}

int Player::get_num_turns() const
{
	return num_turns_in_jail;
}

bool Player::is_bankrupt(double amount)
{
	double total = balance().second;
	if (amount > total)
		return true;
	else
		return false;
}

std::pair<double, double> Player::balance()
{
	std::pair<double, double> balance;
	balance.first = m_wallet;
	
	double props_val = 0;
	double utils_val = 0;
	double rails_val = 0;
	
	std::vector<Property*> my_props = get_properties();
	unsigned size = my_props.size();
	for(unsigned i=0; i<size; i++)
	{
		props_val += my_props[i]->getMortgage();
		int buildings = my_props[i]->getNumBuildings();
		if(buildings)
			props_val += buildings * my_props[i]->getHousePrice()/2; 
	}
	
	// both utils have the same mortgage value
	std::vector<Utility*> my_utils = get_utilities();
	utils_val += my_utils[0]->getMortgage() * my_utils.size();
	
	// all rails have the same mortgage value
	std::vector<Railroad*> my_rails = get_railroads();
	rails_val += my_rails[0]->getMortgage() * my_rails.size();
	
	balance.second = props_val + utils_val + rails_val + m_wallet;
	
	return balance;
}

void Player::pay(double amount)
{
	m_wallet -= amount;
}

void Player::receive(double amount)
{
	m_wallet += amount;
}

// TODO: void move(int i) -> pokrece se i polja po tabli => treba neko ko ima pristup tabli da pomera (Game)
// TODO: void build(std::string building)

void Player::set_name(std::string name){
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

std::vector<Property*> Player::get_properties() const{
    return owned_properties;
}

std::vector<Utility*> Player::get_utilities() const{
    return owned_utilities;
}

std::vector<Railroad*> Player::get_railroads() const{
    return owned_railroads;
}

std::vector<Space*> Player::get_spaces() const{
    return owned_spaces;
}

bool Player::check_properties(Property* p)
{
	std::vector<Property*> my_properties = get_properties();		
	std::string colour = p->getColour();
	int count = 0;
	unsigned i = 0;
	bool has_all = false;
	if(colour == "D_BLUE" || colour == "L_BLUE")
		count = 1;
	for(; i < my_properties.size(); i++)
	{
		if(my_properties[i]->getColour() == colour && my_properties[i]->getNumBuildings() == 0)
			count ++;
	}		
	
	if(count == 3)
		has_all = true;
	
	return has_all;
}

bool Player::check_utilities()
{
	bool has_all = false;
	std::vector<Utility*> my_utilities = get_utilities();
	if(my_utilities.size() == 2)
		has_all = true;
	return has_all;
}

int Player::check_railroads()
{
	std::vector<Railroad*> my_railroads = get_railroads();
	return my_railroads.size();
}

void Player::add_space(Space* s){
    owned_spaces.push_back(s);
}

void Player::init_wallet()
{
	m_wallet = 1500;
}
