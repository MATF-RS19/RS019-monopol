#include "Bank.hpp" 

Bank::Bank(){
    
}

void Bank::sellSpace(Player *player, Space *space){
    //TODO: check balance in Player::pay
    player->pay(space->getBuyPrice());
    player->add_space(space);
    space->setOwned();
    space->setOwner(player->getId());
}

int Bank::getHouses() const{
    return m_houses;
}

void Bank::setHouses(int num){
    m_houses = num;
}

int Bank::getHotels() const{
    return m_hotels;
}

void Bank::setHotels(int num){
    m_hotels = num;
}
