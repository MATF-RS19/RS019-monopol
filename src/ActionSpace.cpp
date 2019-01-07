#include "ActionSpace.hpp" 

std::string ActionSpace::getName() const {
    return "ActionSpace";
}

//NOTE: These are all dummy functions overridden from Space class
//      and should never be called
//TODO: Find better solution for this kind of ineheritance
void ActionSpace::setOwner(int id) {
    (void)id;
}

int ActionSpace::getOwner() const {
    return -1;
}

void ActionSpace::setOwned(){
    
}

bool ActionSpace::isOwned() const {
    return false;    
}

double ActionSpace::getBuyPrice() const {
    return -1;
}

int ActionSpace::getAction() const {
    return m_action;
}

int ActionSpace::getNumBuildings() const {
    return -1;
}

std::string ActionSpace::getGroup() const {
    return "ActionSpace";
}

void ActionSpace::printSpace() const {
    std::cout << ActionSpace::getAction() << std::endl;
}

void ActionSpace::doAction(Player* p) {
	int action = getAction();
	
	if(action == 0)
	{
		//TODO: napraviti da se dovuce poruka kartice i ko ju je izvukao :)))))))))))
		//Player* p; -- current player
		//players -- all players
		//TODO: ovde se izvlaci broj kartice 
		unsigned card_num = 0;
		if(card_num == 0)
		{
//			p->setMPos(0, 0);
//			p->receive(200.0);
		}
		else if(card_num == 1)
		{
// 			if(ill pos - p->getMPos() < 0)
// 				p->receive(200.0);
// 			p->setMPos(illinois);
		}
		else if(card_num == 2)
		{
// 			if(stcharles pos - p->getMPos() < 0)
// 				p->receive(200.0);
// 			p->setMPos(stcharles);
		}
		else if(card_num == 3)
		{
			//to nearest utility;
			//check if owned; roll dice again and pay 10*amount
			//else, offer to buy
		}
		else if(card_num == 4)
		{
			//to nearest railroad;
			//check if owned; roll dice again and pay 2*amount
			//else, offer to buy			
		}
		else if(card_num == 5)
		{
			//to nearest railroad;
			//check if owned; roll dice again and pay 2*amount
			//else, offer to buy			
		}
		else if(card_num == 6)
		{
			p->receive(50.0);
		}
		else if(card_num == 7)
		{
			if(p->is_in_jail())
				p->release_from_jail();
			else
				p->receive_jail_card();
		}
		else if(card_num == 8)
		{
			//p->setMPos(p->getMPos()-3);
		}
		else if(card_num == 9)
		{
			p->send_to_jail();
		}
		else if(card_num == 10)
		{
			std::vector<Property*> props = p->get_properties();
			unsigned size = props.size();
			int num = 0;
			for(unsigned i=0; i<size; i++)
				num += props[i]->getNumBuildings();
			
			p->pay(num * 25.0);
		}
		else if(card_num == 11)
		{
			p->pay(15.0);
		}
		else if(card_num == 12)
		{
//			if(reading - p->getMPos() < 0)
// 			p->receive(200.0);
// 			p->setMPos(reading);
		}
		else if(card_num == 13)
		{
// 			p->setMPos(boardwalk);			
		}
		else if(card_num == 14)
		{
			p->pay(50.0); // * num_players - 1 
			//all others->receive(50.0)
		}
		else if(card_num == 15)
		{
			p->receive(150.0);
		}
		else if(card_num == 16)
		{
			p->receive(100.0);
		}
	}
	else if(action == 1)
	{
		//TODO: napraviti da se dovuce poruka kartice i ko ju je izvukao :)))))))))))
		//Player* p; -- current player
		//players -- all players
		//TODO: ovde se izvlaci broj kartice 
		unsigned card_num = 0;
		if(card_num == 17)
		{
//			p->setMPos(0, 0);
//			p->receive(200.0);
		}
		else if(card_num == 18)
		{
			p->receive(200.0);
		}
		else if(card_num == 19)
		{
			p->pay(50.0);
		}
		else if(card_num == 20)
		{
			p->receive(50.0);
		}
		else if(card_num == 21)
		{
			if(p->is_in_jail())
				p->release_from_jail();
			else
				p->receive_jail_card();
		}
		else if(card_num == 22)
		{
			p->send_to_jail();
		}
		else if(card_num == 23)
		{
			p->receive(50.0); // * num_players - 1 
			//all others->pay(50.0)
		}
		else if(card_num == 24)
		{
			p->receive(100.0);
		}
		else if(card_num == 25)
		{
			p->receive(20.0);
		}
		else if(card_num == 26)
		{
			p->receive(10.0); // * num_players - 1 
			//all others->pay(10.0)
		}
		else if(card_num == 27)
		{
			p->receive(100.0);
		}
		else if(card_num == 28)
		{
			p->pay(50.0);
		}
		else if(card_num == 29)
		{
			p->pay(50.0);
		}
		else if(card_num == 30)
		{
			p->receive(25.0);
		}
		else if(card_num == 31)
		{
			std::vector<Property*> props = p->get_properties();
			unsigned size = props.size();
			int num = 0;
			int num_h = 0;
			double total = 0;
			for(unsigned i=0; i<size; i++)
			{
				int num_h = props[i]->getNumBuildings();
				if(num_h == 5)
					total += 115;
				else
					num += num_h;
			}		
			p->pay(num * 40.0 + total);
		}
		else if(card_num == 32)
		{
			p->receive(10.0);
		}
		else if(card_num == 33)
		{
			p->receive(100.0);
		}
	}
	else if(action == 2)
	{
		p->send_to_jail();
	}
	else if(action == 3)
	{
		p->pay((double)200);
	}
	// action 4 (free parking) -- nothing happens
	else if(action == 5)
	{
		p->pay((double)75);
	}
	else if(action == 6)
	{
		p->receive((double)200);
	}
	else if(action == 7)
	{
		// za sad nek samo stoji tu 3 kruga i na kraju plati
		if(p->is_in_jail())
		{
			if(p->get_num_turns() == 3)
			{
				p->pay((double)50);
				p->release_from_jail();
			}
			else
				p->set_num_turns(p->get_num_turns()+1);
		}
	}
	
	return;
}