#pragma once

#include "Space.hpp"
#include "Player.hpp"

class Player;

class Utility : public Space
{
public:
	Utility(double buy_price, double mortgage, std::string group)
	: _buy_price(buy_price), _mortgage(mortgage), _group(group)
	{}
	
	static std::vector<Utility*> initialize_utilities();

	virtual void printSpace() const override;

    virtual std::string getInfo() const override;

	double getBuyPrice() const {
		return _buy_price;
	}

	std::string getName() const {
		return _group;
	}
	
	std::string getType() const {
		return "UTILITY";
    }
    
    double getMortgage() const {
		return _mortgage;
    }
	
	bool isOwned() const override {
        return _owned;
    }
    
    void setOwner(int id) {
        id_owner = id;
    }
	
	int getOwner() const {
        return id_owner;
    }
	
	void setOwned() {
        _owned = true;
    }
    
    int getNumBuildings() const override;

	void setNumBuildings(int num) override;
    
    std::string getGroup() const override;
    
    int getAction() const override;
	
	void setMortgage(Player* p);
	void revertMortgage(Player* p);
	bool isOnMortgage() const {
		return _is_on_mortgage;
	}

private:
	double _buy_price, _mortgage;
	std::string _group;
    bool _owned = false;
	bool _is_on_mortgage = false;
    int id_owner = -1;
};

