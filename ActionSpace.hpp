#pragma once

#include "Space.hpp"

class ActionSpace : public Space{

	public:
		ActionSpace(int action)
        : m_action(action)
        {}
        
		
 		enum class EnumActionSpace
         {
             CHANCE,
             COMMUNITY_CHEST,
             GOTO_JAIL,
             INCOME_TAX,
             FREE_PARKING,
             LUXURY_TAX,
             GO
         };

	private:
		int m_action;

};
