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
        numPlayers--;
        players.push_back(p);
    }
    
    return players;
}


//TODO: dodati konstruktor sa argumentima
//NOTE: ne moze se koristiti clanska promenljva pre nego sto se napravi klasa => ne moze m_obj_count u konstruktoru ?
// Player::Player()
// 	: m_id(m_obj_count)
// {
// 	m_obj_count++;
// }

Player::Player()
{
    //TODO: implement me, mada ja mislim da nije potreban konstruktor bez argumenata
}

Player::~Player()
{
	//m_obj_count--;
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

// TODO: void move()
// TODO: void build(std::string building)

void Player::set_name(std::string name)
{
	m_name = name;
}

std::string Player::get_name() const{
    return m_name;
}
