#pragma once

#include "Space.hpp"
#include "Player.hpp" 
#include <iostream>

class Player;

class ActionSpace : public Space {
	public:
		ActionSpace(int action)
        	: m_action(action)
       		{
            }
        
        int getAction() const override;
        
		void printSpace() const override;

        std::string getName() const override;
        
        double getBuyPrice() const override;
        
        bool isOwned() const override;
        
        void setOwned() override;
        
        void setOwner(int id) override;
        
        int getOwner() const override;
        
        int getNumBuildings() const override;

		void setNumBuildings(int num) override;
        
        std::string getGroup() const override;
		std::string getInfo() const;
		
		std::string getSpaceAction();
		
		void doAction(Player* p) {
			return;
		}
		
		std::string getType() const {
			return "ACTION SPACE";
		}
		
		bool isOnMortgage() const {
			return false;
		}
		
		double getRentPrice() const {
		return 0;
		}
		
		double getH1Price() const {
			return 0;
		}
		
		double getH2Price() const {
			return 0;
		}
		
		double getH3Price() const {
			return 0;
		}
		
		double getH4Price() const {
			return 0;
		}
		
		double getH5Price() const {
			return 0;
		}
		
		std::string getColour() const {
			return "TRANSPARENT";
		}

 		enum class EnumActionSpace
		{
			CHANCE,
			COMMUNITY_CHEST,
			GOTO_JAIL,
			INCOME_TAX,
			FREE_PARKING,
			LUXURY_TAX,
			GO,
			JAIL
		};
private:
	int m_action;
};
