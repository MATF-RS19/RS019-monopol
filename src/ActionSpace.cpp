#include "ActionSpace.hpp" 

std::string ActionSpace::getName() const{
    return "ActionSpace";
}

void ActionSpace::printSpace() const{
	std::cout << ActionSpace::getAction() << std::endl;	
}

void ActionSpace::doAction(Player* p) {
	int action = getAction();
	
	if(action == 0)
	{
		
	}
	else if(action == 1)
	{
		
	}
	else if(action == 2)
	{
		p->send_to_jail();
	}
	else if(action == 3)
	{
		p->pay(200);
	}
	// action 4 (free parking) -- nothing happens
	else if(action == 5)
	{
		p->pay(75);
	}
	else if(action == 6)
	{
		p->receive(200);
	}
	else if(action == 7)
	{
		// za sad nek samo stoji tu 3 kruga i na kraju plati
		if(p->is_in_jail())
		{
			if(p->get_num_turns() == 3)
			{
				p->pay(50);
				p->release_from_jail();
			}
			else
				p->set_num_turns(p->get_num_turns()+1);
		}
	}
	
	return;
}
