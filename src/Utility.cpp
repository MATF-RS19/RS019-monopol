#include "Utility.hpp"

void Utility::printSpace() const {
	std::cout << "Utility: " << Utility::getName() << ", price: " << Utility::getBuyPrice() << std::endl; 
}

std::string Utility::getGroup() const {
    return "Utility";
}

int Utility::getNumBuildings() const {
    return -1;
}

std::vector<Utility*> Utility::initialize_utilities()
{
	Utility* water_works = new Utility(150, 75, "WATER_WORKS");
	Utility* electric_company = new Utility(150, 75, "ELECTRIC_COMPANY");
	std::vector<Utility*> utilities = {water_works, electric_company};
	return utilities;
}

int Utility::getAction() const {
    return -1;
}

void Utility::setMortgage(Player* p) {
	_is_on_mortgage = true;
	p->receive(_mortgage);
}

void Utility::revertMortgage(Player* p) {
	_is_on_mortgage = false;
	p->pay(_mortgage*1.1);
}
