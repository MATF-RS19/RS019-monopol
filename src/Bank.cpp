#include "Bank.hpp" 

Bank::Bank(){
    
}

void Bank::sellSpace(Player *player, Space *space) {
    //Make sure not to sell already owned space
    if(!space->isOwned()){
        player->pay(space->getBuyPrice());
        player->add_space(space);
        space->setOwned();
        space->setOwner(player->getId());

        //HACK: downcast to appropriate subclass and add it to list of
        //properties/utilities/railroads for usage in other functions
        std::string type = space->getType();
        switch (type.at(0)) {
            case 'U' :
                player->add_utility(dynamic_cast<Utility*>(space));
            break;
            case 'P':
                player->add_property(dynamic_cast<Property*>(space));
            break;
            case 'R':
                player->add_railroad(dynamic_cast<Railroad*>(space));
            break;
            default:
            break;

        }
    }

}

int Bank::getHouses() const {
    return m_houses;
}

void Bank::setHouses(int num) {
    m_houses = num;
}

int Bank::getHotels() const {
    return m_hotels;
}

void Bank::setHotels(int num) {
    m_hotels = num;
}
