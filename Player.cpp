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

bool is_in_jail() const
{
	return m_in_jail;
}

void send_to_jail()
{
	if (m_in_jail == true) return;

	m_in_jail = true;
}

void release_from_jail()
{
	if (m_in_jail == false) return;

	m_in_jail = false;
}

int balance() const
{
	return m_wallet;
}

void pay(int amount)
{
	m_wallet -= amount;
}

void receive(int amount)
{
	m_wallet += amount;
}

const Coordinate& position() const
{
	return m_pos;
}

// TODO: void move()
// TODO: void build(std::string building)

void set_name(std::string name)
{
	m_name = name;
}
