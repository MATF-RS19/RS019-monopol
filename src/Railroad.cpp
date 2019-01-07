#include "Railroad.hpp"

void Railroad::printSpace() const {
	std::cout << "Railroad: " << Railroad::getName() << ", price: " << Railroad::getBuyPrice() << std::endl;
}

std::string Railroad::getGroup() const {
    return "Railroad";
}

int Railroad::getNumBuildings() const {
    return -1;
}

std::vector<Railroad*> Railroad::initialize_railroads()
{
	Railroad* reading = new Railroad(200, 25, 100, "Reading railroad");
	Railroad* penn = new Railroad(200, 25, 100, "Pennsylvania Railroad");
	Railroad* bo = new Railroad(200, 25, 100, "B. & O. Railroad");
	Railroad* sl = new Railroad(200, 25, 100, "Short Line");	
	
	std::vector<Railroad*> railroads = {reading, penn, bo, sl};
	return railroads;	
}

int Railroad::getAction() const {
    return -1;
}

void Railroad::setMortgage(Player* p) {
	_is_on_mortgage = true;
	p->receive(_mortgage);
}

void Railroad::revertMortgage(Player* p) {
	_is_on_mortgage = false;
	p->pay(_mortgage*1.1);
}