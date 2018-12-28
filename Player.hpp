#ifndef PLAYER_H
#define PLAYER_H

class Coordinate {
public:
	Coordinate(unsigned x, unsigned y);

	~Coordinate();
	
private:
	unsigned x, y;
}

class Player {
public:
	
	static int m_obj_count;

	Player();

	~Player();

	Player(const Player& other) = delete;

	Player& operator= (const Player& other) = delete;

	bool is_in_jail() const;
	void send_to_jail();
	void release_from_jail();

	int balance() const;
	void pay(int amount);
	void receive(int amount);

	const Coordinate& position() const;
	void move();

	void build(std::string building);
	
	void set_name(std::string name);

private:
	unsigned m_id;
	std::string name;
	Coordinate m_pos;	// position of player
	int m_wallet; // player's money
	bool m_in_jail;

	// m_houses[name_of_property] = num_of_houses
	std::map<std::string, int> m_houses;
	// m_hotels[name_of_property] = num_of_hotels
	std::map<std::string, int> m_hotels;
	// TODO?: [???] instead of std::string
	std::map<std::string, int> m_property_fields;

	friend std::ostream & operator << (std::ostream& out, const player& value);
	// do we need this?
//	friend std::istream & operator >> (std::istream& in, player& value);
};

std::ostream & operator << (std::ostream& out, const player& value);
// std::istream & operator >> (std::istream& in, player& value);

#endif
