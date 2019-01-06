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

int Player::balance() const
{
	return m_wallet;
}

void Player::pay(int amount)
{
	m_wallet -= amount;
}

void Player::receive(int amount)
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
		if(my_properties[i]->getColour() == colour)
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
