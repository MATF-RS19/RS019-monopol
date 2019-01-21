#include "Utility.hpp"

std::string Utility::getInfo() const {
	std::ostringstream info;
	info << getName() << std::endl;
	if(!isOwned())
		info << "Not owned" << std::endl;
	else
		info << "Owned by playerId: " << getOwner() << std::endl;
	info << "RENT $" << "number on dice * 4" << std::endl;
	info << "Mortgage value $75" << std::endl;
	info << "If a player owns BOTH utilities, the rent is number on dice * 10" << std::endl;
	return info.str();
}

void Utility::printSpace() const {
	std::cout << "Utility: " << Utility::getName() << ", price: " << Utility::getBuyPrice() << std::endl; 
}

std::string Utility::getGroup() const {
    return _group;
}

int Utility::getNumBuildings() const {
    return -1;
}

void Utility::setNumBuildings(int num) {
	return;
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
