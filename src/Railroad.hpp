#pragma once

#include "Space.hpp"
#include "Player.hpp"
#include <iterator>

class Player;

class Railroad : public Space
{
public:
	Railroad(double buy_price, double rent_price, double mortgage, std::string name)
	: _buy_price(buy_price), _rent_price(rent_price), _mortgage(mortgage), _name(name)
	{}
	
	static std::vector<Railroad*> initialize_railroads();

    std::string getInfo() const;

    std::string getName() const override;
	
    std::string getType() const override;
    
    double getMortgage() const;

    double getBuyPrice() const override;
	
    double getRentPrice() const override;
	
    bool isOwned() const override;
	
    void setOwner(int id) override;
    
    int getOwner() const override;
	
    void setOwned() override;

	std::vector<int> player() const override;
	
	void addPlayer(int p) override; 

	void removePlayer(int p) override;

    int getNumBuildings() const override;

	void setNumBuildings(int num) override;
    
    void setIsOnMortgage();

	void printSpace() const override;
    
    std::string getGroup() const override;
    
    int getAction() const override;
	
    void doAction(Player* p) override{
        return;
    }

	void setMortgage(Player* p);
	void revertMortgage(Player* p);
    bool isOnMortgage() const override;
	
    double getH1Price() const override{
		return 0;
	}
	
    double getH2Price() const override{
		return 0;
	}
	
    double getH3Price() const override{
		return 0;
	}
	
    double getH4Price() const override{
		return 0;
	}
	
    double getH5Price() const override{
		return 0;
	}
	
    std::string getColour() const override{
		return "TRANSPARENT";
	}
    
private:
	double _buy_price,  _rent_price, _mortgage;
	std::string _name;
    bool _owned = false;
	bool _is_on_mortgage = false;
    int id_owner = -1;
	std::vector<int> m_player = {};
};
