#pragma once

#include "Space.hpp"
#include <string>
#include <vector>

//using namespace std;

class Utility : public Space
{
public:
	Utility(double buy_price, double mortgage, std::string group)
	: _buy_price(buy_price), _mortgage(mortgage), _group(group)
	{}
	
	static std::vector<Utility*> initialize_utilities();
private:
	double _buy_price, _mortgage;
	std::string _group;
};

