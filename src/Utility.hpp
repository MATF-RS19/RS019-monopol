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

    void doAction(Player* p) override{
        return;
    }

    double getBuyPrice() const override{
		return _buy_price;
	}

    std::string getName() const override{
		return _group;
	}
	
    std::string getType() const override{
		return "UTILITY";
    }
    
    double getMortgage() const {
		return _mortgage;
    }
	
	bool isOwned() const override {
        return _owned;
    }
    
    void setOwner(int id) override{
        id_owner = id;
    }
	
    int getOwner() const override{
        return id_owner;
    }
	
    void setOwned() override{
        _owned = true;
    }
    
    int getNumBuildings() const override;

	void setNumBuildings(int num) override;
    
    std::string getGroup() const override;
	std::string getInfo() const;
    
    int getAction() const override;
	
	void setMortgage(Player* p);
	void revertMortgage(Player* p);
    bool isOnMortgage() const override{
		return _is_on_mortgage;
	}
	
    double getRentPrice() const override{
		return 0;
	}
	
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

    void setIsOnMortgage(){
        _is_on_mortgage = true;
    }

private:
	double _buy_price, _mortgage;
	std::string _group;
    bool _owned = false;
	bool _is_on_mortgage = false;
    int id_owner = -1;
};

