#include "Railroad.hpp"

std::string Railroad::getInfo() const {
	std::ostringstream info;
	info << getName() << std::endl;
	if(!isOwned())
		info << "Not owned" << std::endl;
	else
		info << "Owned by playerId: " << getOwner() << std::endl;
	info << "RENT $25" << std::endl;
	info << "Mortgage value $100" << std::endl;
	info << "If a player owns 2 railroads, the rent is $50, 3 railroads $100 and all of them $200." << std::endl;
	return info.str();
}

void Railroad::printSpace() const {
	std::cout << "Railroad: " << Railroad::getName() << ", price: " << Railroad::getBuyPrice() << std::endl;
}

std::string Railroad::getGroup() const {
    return "Railroad";
}

int Railroad::getNumBuildings() const {
    return -1;
}

void Railroad::setNumBuildings(int num) {
	return;
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

std::vector<int> Railroad::player() const {
	return m_player;
}

void Railroad::addPlayer(int p) {
	m_player.push_back(p);
}

void Railroad::removePlayer(int p) {
	m_player.erase(std::remove(m_player.begin(), m_player.end(), p),
				   m_player.end());
}

void Railroad::setIsOnMortgage(){
    _is_on_mortgage = true;
}

bool Railroad::isOnMortgage() const{
    return _is_on_mortgage;
}
