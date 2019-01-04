#pragma once

#include "Space.hpp"
#include <string>
#include <vector>

class Property : public Space
{
public:
	Property(double buy_price, double rent_price, double h1_price, double h2_price, double h3_price, double h4_price, double h5_price, double mortgage, double house_price, std::string name, std::string colour)
		: _buy_price{buy_price}, _rent_price{rent_price}, _h1_price{h1_price}, _h2_price{h2_price}, _h3_price{h3_price}, _h4_price{h4_price}, _h5_price{h5_price}, _mortgage{mortgage}, _house_price{house_price}, _name{name}, _colour{colour}
		{}
		
	static std::vector<Property*> initialize_properties();

	virtual void printSpace() const override;

	std::string getName() const{
		return _name;
	}

	double getBuyPrice() const{
        //std::cout << "Property" << std::endl;
		return _buy_price;
	}
	
	int getNumBuildings() const{
        return _num_buildings;
    }
    
    void setNumBuildings(int num){
        _num_buildings = num;
    }
    
    bool isOwned() const override{
        return _owned;
    }
    
    void setOwned() override{
        _owned = true;
    }
private:
	double _buy_price, _rent_price, _h1_price, _h2_price, _h3_price, _h4_price, _h5_price, _mortgage, _house_price;
	std::string _name, _colour;
    int _num_buildings;
    bool _owned = false;
};
