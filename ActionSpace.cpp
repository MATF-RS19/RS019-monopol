#include "ActionSpace.hpp" 

std::string ActionSpace::getName() const{
    
    return "ActionSpace";
    
}

void ActionSpace::printSpace() const{

	std::cout << ActionSpace::getAction() << std::endl;	

}
