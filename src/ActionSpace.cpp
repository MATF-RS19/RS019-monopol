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

std::string ActionSpace::getInfo() const{
    return "";
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

void ActionSpace::setNumBuildings(int num) {
	return;
}

std::string ActionSpace::getGroup() const {
    return "ActionSpace";
}

void ActionSpace::printSpace() const {
    std::cout << ActionSpace::getAction() << std::endl;
}

std::string ActionSpace::getSpaceAction(){
    ActionSpace::EnumActionSpace action = static_cast<ActionSpace::EnumActionSpace>(getAction());
    switch (action) {
        case ActionSpace::EnumActionSpace::CHANCE :
            std::cout << "DRAW CHANCE CARD" << std::endl;
			return "CHANCE";
        break;
        case ActionSpace::EnumActionSpace::COMMUNITY_CHEST :
            std::cout << "DRAW COMMUNITY CHEST CARD" << std::endl;
			return "COMMUNITY_CHEST";
        break;
    case ActionSpace::EnumActionSpace::FREE_PARKING :
        std::cout << "FREE PARKING" << std::endl;
		return "FREE_PARKING";
        break;
    case ActionSpace::EnumActionSpace::GO :
        std::cout << "GO" << std::endl;
		return "GO";
        break;
    case ActionSpace::EnumActionSpace::GOTO_JAIL :
        std::cout << "GO TO JAIL" << std::endl;
		return "GOTO_JAIL";
        break;
    case ActionSpace::EnumActionSpace::INCOME_TAX :
        std::cout << "INCOME TAX" << std::endl;
		return "INCOME_TAX";
        break;
    case ActionSpace::EnumActionSpace::JAIL :
        std::cout << "JAIL" << std::endl;
		return "JAIL";
        break;
    case ActionSpace::EnumActionSpace::LUXURY_TAX :
        std::cout << "LUXURY TAX" << std::endl;
		return "LUXURY_TAX";
        break;
    default:
		return "ERROR";
        break;
    }
}

