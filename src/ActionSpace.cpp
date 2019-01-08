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

//TODO: popraviti ovo da ima smisla

void ActionSpace::doAction(Player* p){
    ActionSpace::EnumActionSpace action = static_cast<ActionSpace::EnumActionSpace>(getAction());
    switch (action) {
        case ActionSpace::EnumActionSpace::CHANCE :
            std::cout << "DRAW CHANCE CARD" << std::endl;
        break;
        case ActionSpace::EnumActionSpace::COMMUNITY_CHEST :
            std::cout << "COmm" << std::endl;
        break;
    case ActionSpace::EnumActionSpace::FREE_PARKING :
        std::cout << "FREE PARK" << std::endl;
        break;
    case ActionSpace::EnumActionSpace::GO :
        std::cout << "GO" << std::endl;
        break;
    case ActionSpace::EnumActionSpace::GOTO_JAIL :
        std::cout << "Jail" << std::endl;
        break;
    case ActionSpace::EnumActionSpace::INCOME_TAX :
        std::cout << "INcome tax" << std::endl;
        break;
    case ActionSpace::EnumActionSpace::JAIL :
        std::cout << "JAIL" << std::endl;
        break;
    case ActionSpace::EnumActionSpace::LUXURY_TAX :
        std::cout << "Luc" << std::endl;
        break;
    default:
        break;
    }
}

