#pragma once

#include "Space.hpp"
#include <string>
#include <vector>
#include <iostream>

class Utility : public Space
{
public:
	Utility(double buy_price, double mortgage, std::string group)
	: _buy_price(buy_price), _mortgage(mortgage), _group(group)
	{}
	
	static std::vector<Utility*> initialize_utilities();

	virtual void printSpace() const override;

	double getBuyPrice() const{
		return _buy_price;
	}

	std::string getName() const{
		return _group;
	}
	
	bool isOwned() const override{
        return _owned;
    }
	
	void setOwned(){
        _owned = true;
    }
    
    std::string getType() const {
		return "UTILITY";
    }

private:
	double _buy_price, _mortgage;
	std::string _group;
    bool _owned = false;
};

