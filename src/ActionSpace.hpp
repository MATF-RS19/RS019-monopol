#pragma once

#include "Space.hpp"
#include "Player.hpp"
#include <iostream>

class Player;

class ActionSpace : public Space{

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
        
        std::string getGroup() const override;
		
		void doAction(Player* p);
		
		std::string getType() const{
			return "ACTION SPACE";
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
