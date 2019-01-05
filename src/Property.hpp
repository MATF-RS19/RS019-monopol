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
	
	std::string getColour() const{
        return _colour;
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
    
    void setOwner(int id){
        std::cout << "Hey" << std::endl;
        id_owner = id;
    }
    
    int getOwner() const{
        return id_owner;
    }
    
    std::string getGroup() const override;
    
    int getAction() const override;
    
private:
	double _buy_price, _rent_price, _h1_price, _h2_price, _h3_price, _h4_price, _h5_price, _mortgage, _house_price;
	std::string _name, _colour;
    int _num_buildings = 0;
    bool _owned = false;
    //FIXME: should be something like ref to Player object
    int id_owner;
    
};
