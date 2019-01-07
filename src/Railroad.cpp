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

std::string Railroad::getName() const{
    return _name;
}

std::string Railroad::getType() const{
    return "RAILROAD";
}

std::string Railroad::getInfo() const{
    std::ostringstream info;
    info << getName() << std::endl;
    info << "RENT $" << getRentPrice() << std::endl;
    info << "Owned by playerId: " << getOwner() << std::endl;
    //TODO: add getOwnerName method => this implies that all of the Space class instances
    //      should have ref to owner (Player class object)
    return info.str();
}

void Railroad::setMortgage(Player* p) {
	_is_on_mortgage = true;
	p->receive(_mortgage);
}

double Railroad::getMortgage() const{
    return _mortgage;
}

void Railroad::revertMortgage(Player* p) {
	_is_on_mortgage = false;
	p->pay(_mortgage*1.1);
}

double Railroad::getBuyPrice() const{
    //std::cout << "Railroad" << std::endl;
    return _buy_price;
}

double Railroad::getRentPrice() const {
    return _rent_price;
}

void Railroad::setOwner(int id){
    id_owner = id;
}

int Railroad::getOwner() const{
    return id_owner;
}

void Railroad::setOwned(){
    _owned = true;
}

bool Railroad::isOwned() const{
    return _owned;
}

bool Railroad::isOnMortgage() const{
    return _is_on_mortgage;
}
