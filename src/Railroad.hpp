#pragma once

#include "Space.hpp"
#include "Player.hpp"

class Player;

class Railroad : public Space
{
public:
	Railroad(double buy_price, double rent_price, double mortgage, std::string name)
	: _buy_price(buy_price), _rent_price(rent_price), _mortgage(mortgage), _name(name)
	{}
	
	static std::vector<Railroad*> initialize_railroads();

    virtual std::string getInfo() const override;

    std::string getName() const override;
	
    std::string getType() const override;
    
    double getMortgage() const;

    double getBuyPrice() const override;
	
    double getRentPrice() const;
	
    bool isOwned() const override;
	
    void setOwner(int id) override;
    
    int getOwner() const override;
	
    void setOwned() override;

    int getNumBuildings() const override;

	void setNumBuildings(int num) override;
    
	void printSpace() const override;
    
    std::string getGroup() const override;
    
    int getAction() const override;
	
	void setMortgage(Player* p);
	void revertMortgage(Player* p);
    bool isOnMortgage() const override;
    
private:
	double _buy_price,  _rent_price, _mortgage;
	std::string _name;
    bool _owned = false;
	bool _is_on_mortgage = false;
    int id_owner;
};
