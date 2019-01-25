#pragma once

#include "Space.hpp"
#include "Player.hpp"
#include <QString>
#include <algorithm>
#include <iterator>

class Player;

class Property : public Space
{
public:
	Property(double buy_price, double rent_price, double h1_price, double h2_price, double h3_price, double h4_price, double h5_price, double mortgage, double house_price, std::string name, std::string colour)
		: _buy_price{buy_price}, _rent_price{rent_price}, _h1_price{h1_price}, _h2_price{h2_price}, _h3_price{h3_price}, _h4_price{h4_price}, _h5_price{h5_price}, _mortgage{mortgage}, _house_price{house_price}, _name{name}, _colour{colour}
		{}
		
	static std::vector<Property*> initialize_properties();

	virtual void printSpace() const override;

    std::string getInfo() const override;

    std::string getName() const override{
		return _name;
	}
	
    std::string getColour() const override{
        return _colour;
    }

    double getBuyPrice() const override{
        //std::cout << "Property" << std::endl;
		return _buy_price;
	}
	
    int getNumBuildings() const override{
        return _num_buildings;
    }
    
    double getRentPrice() const override{
		return _rent_price;
    }
    
    double getMortgage() const {
		return _mortgage;
    }
    
    double getHousePrice() const {
		return _house_price;
    }
    
    void setNumBuildings(int num) override{
        _num_buildings = num;
    }
    
    bool isOwned() const override {
        return _owned;
    }
    
    void setOwned() override {
        _owned = true;
    }
    
    void setOwner(int id) override{
        id_owner = id;
    }
    
    int getOwner() const override{
        return id_owner;
    }

	std::vector<int> player() const override {
		return m_player; 
	}

	void addPlayer(int p) override {
		m_player.push_back(p);
	}

	void removePlayer(int p) override {
		m_player.erase(std::remove(m_player.begin(), m_player.end(), p), 
					   m_player.end()); 
	}
    
    std::string getType() const override{
		return "PROPERTY";
    }

    double getH1Price() const override{
		return _h1_price;
    }
    
    double getH2Price() const override{
		return _h2_price;
    }
    
    double getH3Price() const override{
		return _h3_price;
    }
    
    double getH4Price() const override{
		return _h4_price;
    }
    
    double getH5Price() const override{
		return _h5_price;
    }
    
    void setMortgage(Player* p);

    void setIsOnMortgage();

    void revertMortgage(Player* p);
    bool isOnMortgage() const override{
		return _is_on_mortgage;
	}
    
    std::string getGroup() const override;
    
    int getAction() const override;

    void doAction(Player* p) override{
        return;
    }
    
private:
	double _buy_price, _rent_price, _h1_price, _h2_price, _h3_price, _h4_price, _h5_price, _mortgage, _house_price;
	std::string _name, _colour;
    int _num_buildings = 0;
    bool _owned = false;
	bool _is_on_mortgage = false;
    //FIXME: should be something like ref to Player object
    int id_owner = -1;
	std::vector<int> m_player = {};
};
