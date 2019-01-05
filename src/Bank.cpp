#include "Bank.hpp" 

// Use this
void Bank::sellSpace(Player *player, Space *space){
    player->pay(space->getBuyPrice());
    player->add_space(space);
    space->setOwned();
}

void Bank::sellProperty(Player *player, Property *property){
    player->pay(property->getBuyPrice());
    player->add_property(property);
    property->setOwned();
}
