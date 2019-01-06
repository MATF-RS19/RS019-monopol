#pragma once

#include "Space.hpp"
#include "Player.hpp"
#include <string>
#include <iostream>
#include <vector>

class Player;

class Railroad : public Space
{
public:
	Railroad(double buy_price, double rent_price, double mortgage, std::string name)
	: _buy_price(buy_price), _rent_price(rent_price), _mortgage(mortgage), _name(name)
	{}
	
	static std::vector<Railroad*> initialize_railroads();

	std::string getName() const{
		return _name;
	}
	
	std::string getType() const{
		return "RAILROAD";
    }
    
    double getMortgage() const{
		return _mortgage;
    }

	double getBuyPrice() const{
        //std::cout << "Railroad" << std::endl;
		return _buy_price;
	}
	
	int getRentPrice() const{
		return _rent_price;
    }
	
	bool isOwned() const override{
        return _owned;
    }
	
	void setOwner(int id){
        id_owner = id;
    }
    
    int getOwner() const{
        return id_owner;
    }
	
	void setOwned(){
        _owned = true;
    }

    int getNumBuildings() const override;
    
	void printSpace() const override;
    
    std::string getGroup() const override;
    
    int getAction() const override;
	
	void setMortgage(Player* p);
	void revertMortgage(Player* p);
	bool isOnMortgage() const {
		return _is_on_mortgage;
	}
    
private:
	double _buy_price,  _rent_price, _mortgage;
	std::string _name;
    bool _owned = false;
	bool _is_on_mortgage = false;
    int id_owner;
};
