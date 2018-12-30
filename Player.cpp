#include "player.hpp"

Player::Player()
	: m_id(m_obj_count)
{
	m_obj_count++;
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

// TODO
void Player::buy(Space* space)
{
	return;
}

void Player::receive(int amount)
{
	m_wallet += amount;
}

const Coordinate& Player::position() const
{
	return m_pos;
}

// TODO: void move()
// TODO: void build(std::string building)

void Player::set_name(std::string name)
{
	m_name = name;
}
