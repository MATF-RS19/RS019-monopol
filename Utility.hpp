#pragma once

#include <string>

using namespace std;

class Utility
{
public:
	Utility(double buy_price, double mortgage, string group)
	: _buy_price(buy_price), _mortgage(mortgage), _group(group)
	{}
private:
	double _buy_price, _mortgage;
	string _group;
};