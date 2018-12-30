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
        
		virtual void printSpace() const override;
	

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
