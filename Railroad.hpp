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
		return _buy_price;
	}

	virtual void printSpace() const override;
private:
	double _buy_price,  _rent_price, _mortgage;
	std::string _name;
};
