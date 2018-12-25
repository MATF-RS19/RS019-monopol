#pragma once

#include <string>

using namespace std;

class Property
{
public:
	Property(double buy_price, double rent_price, double h1_price, double h2_price, double h3_price, double h4_price, double h5_price, double mortgage, double house_price, double hotel_price, string colour)
		: _buy_price{buy_price}, _rent_price{rent_price}, _h1_price{h1_price}, _h2_price{h2_price}, _h3_price{h3_price}, _h4_price{h4_price}, _h5_price{h5_price}, _mortgage{mortgage}, _house_price{house_price}, _hotel_price{hotel_price}, _colour{colour}
		{}
private:
	// variables that determine the rent prices of a property;
	// h5 is the price for a property that has a hotel nad hotel_price is the amount of money needed to purchase a hotel on that property
	double _buy_price, _rent_price, _h1_price, _h2_price, _h3_price, _h4_price, _h5_price, _mortgage, _house_price, _hotel_price;
	string _colour;
};