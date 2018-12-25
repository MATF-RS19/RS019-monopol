#pragma once

#include <string>

using namespace std;

class Railroad
{
public:
	Railroad(double buy_price, double rent_price, double mortgage, string name)
	: _buy_price(buy_price), _rent_price(rent_price), _mortgage(mortgage), _name(name)
	{}
private:
	double _buy_price,  _rent_price, _mortgage;
	string _name;
};