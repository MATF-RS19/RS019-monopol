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

std::vector<Space*> Player::get_spaces() const{
    return owned_spaces;
}

void Player::add_space(Space* s){
    owned_spaces.push_back(s);
}
