#ifndef PLAYER_H
#define PLAYER_H

#include "Space.hpp"
#include "Property.hpp"
#include "Utility.hpp"
#include "Railroad.hpp"
#include <map>
#include <vector>

class Coordinate {
public:
	Coordinate(unsigned x, unsigned y);

	~Coordinate();
	
private:
	unsigned x, y;
};

class Player {
public:

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

	//const Coordinate& position() const; NOTE: uncomment later
	void move();
	void buy(Space* space);
 	void pay_rent(Space* space, Player* player, int dice);
	void build(std::string building, Property* p);
	
	void set_name(std::string name);
    
    std::string get_name() const;
    
    void add_property(Property* p);
    void add_utility(Utility* u);
    void add_railroad(Railroad* r);
    
    int get_pos() const;
    void set_pos(int pos);
	
	bool check_properties(Property* p, Player* player);
	bool check_utilities(Player* player);
	int check_railroads(Player* player);

    static std::vector<Player*> initializePlayers(int numPlayers);
    
    std::vector<Property*> get_properties() const;
    std::vector<Utility*> get_utilities() const;
	std::vector<Railroad*> get_railroads() const;
    std::vector<Space*> get_spaces() const;
    void add_space(Space *s);
	
	void set_num_turns(int num);
	int get_num_turns() const;
    
private:
    static int m_obj_count;
	unsigned m_id;
	std::string m_name;
	//Coordinate m_pos;	// position of player NOTE: uncomment later
	int m_wallet; // player's money
	bool m_in_jail;
	int num_turns_in_jail;
	std::vector<Property*> owned_properties;
    std::vector<Utility*> owned_utilities;
    std::vector<Railroad*> owned_railroads;
    
    std::vector<Space*> owned_spaces;
	int m_pos;

	// m_houses[name_of_property] = num_of_houses
	std::map<std::string, int> m_houses;
	// m_hotels[name_of_property] = num_of_hotels
	std::map<std::string, int> m_hotels;
	// TODO?: [???] instead of std::string
	std::map<std::string, int> m_property_fields;

	friend std::ostream & operator << (std::ostream& out, const Player& value);
	// do we need this?
//	friend std::istream & operator >> (std::istream& in, player& value);
};

std::ostream & operator << (std::ostream& out, const Player& value);
// std::istream & operator >> (std::istream& in, player& value);

#endif
