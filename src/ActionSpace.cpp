#include "ActionSpace.hpp" 

std::string ActionSpace::getName() const{
    return "ActionSpace";
}

//NOTE: These are all dummy functions overridden from Space class
//      and should never be called
//TODO: Find better solution for this kind of ineheritance
void ActionSpace::setOwner(int id){
    (void)id;
}

int ActionSpace::getOwner() const{
    return -1;
}

void ActionSpace::setOwned(){
    
}

bool ActionSpace::isOwned() const {
    return false;    
}

double ActionSpace::getBuyPrice() const{
    return -1;
}

int ActionSpace::getAction() const{
    return m_action;
}

int ActionSpace::getNumBuildings() const{
    return -1;
}

std::string ActionSpace::getGroup() const{
    return "ActionSpace";
}

void ActionSpace::printSpace() const{
    std::cout << ActionSpace::getAction() << std::endl;
}
