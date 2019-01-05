#pragma once

#include "Space.hpp"
#include <iostream>

class ActionSpace : public Space{

	public:
		ActionSpace(int action)
        	: m_action(action)
       		{}
        
        int getAction() const{
			return m_action;
		}
        
		void printSpace() const override;

        std::string getName() const override;
        
        double getBuyPrice() const override{
            return -1;
        }
        
        bool isOwned() const override{
            return false;
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
			
		std::string getType() const {
			return "ACTION SPACE";
		}

	private:
		int m_action;

};
