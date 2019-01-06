#pragma once

#include "Space.hpp"
#include "Property.hpp"
#include "Utility.hpp"
#include "Railroad.hpp"
#include "ActionSpace.hpp"
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

    int getId() const;
    
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
	void buy(Space* space); // NOTE: not necessary, bank sells properties
	//void build(Property* property); // build on this property TODO: zabrani nasledjivanje Property klase 
    //TODO: unique pointeri na property
    //TODO: implementacija move semantike
    
	
	void set_name(std::string name);
    
    std::string get_name() const;
    
    void add_property(Property* p);
    void add_utility(Utility* p);
    void add_railroad(Railroad* p);
    
    int get_pos() const;
    
    void set_pos(int pos);

    static std::vector<Player*> initializePlayers(int numPlayers);
    
    std::vector<Property*> get_properties() const;
    std::vector<Utility*> get_utilities() const;
    std::vector<Railroad*> get_railroads() const;
	
	bool check_properties(Property* p);
	bool check_utilities();
	int check_railroads();
    
    std::vector<Space*> get_spaces() const;
    void add_space(Space *s);
	
	void set_num_turns(int num);
	int get_num_turns() const;
    
private:
    static int m_obj_count;
	unsigned m_id;
	std::string m_name;
	int m_wallet; // player's money
	bool m_in_jail;
	std::vector<Property*> owned_properties;
    std::vector<Utility*> owned_utilities;
    std::vector<Railroad*> owned_railroads;
    
    std::vector<Space*> owned_spaces;
	int m_pos;
	int num_turns_in_jail;

	friend std::ostream & operator << (std::ostream& out, const Player& value);
//	friend std::istream & operator >> (std::istream& in, player& value);
};

std::ostream & operator << (std::ostream& out, const Player& value);
// std::istream & operator >> (std::istream& in, player& value);
