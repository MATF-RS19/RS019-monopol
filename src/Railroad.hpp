#pragma once

#include "Space.hpp"
#include <string>
#include <iostream>
#include <vector>

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

	double getBuyPrice() const{
        //std::cout << "Railroad" << std::endl;
		return _buy_price;
	}
	
	double getRentPrice() const{
        //std::cout << "Railroad" << std::endl;
		return _rent_price;
	}
	
	bool isOwned() const override{
        return _owned;
    }
	
	void setOwned(){
        _owned = true;
    }
    
    std::string getType() const {
		return "RAILROAD";
    }

	virtual void printSpace() const override;
private:
	double _buy_price,  _rent_price, _mortgage;
	std::string _name;
    bool _owned = false;
};
