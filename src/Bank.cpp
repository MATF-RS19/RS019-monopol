#include "Bank.hpp" 

Bank::Bank()
{
}

Bank::Bank(int houses, int hotels)
    :m_houses(houses), m_hotels(hotels)
{
}

void Bank::sellSpace(Player *player, Space *space) {
    //Make sure not to sell already owned space
    if(!space->isOwned()){
        qDebug() << "SELLSPACE DEBUG";
        player->pay(space->getBuyPrice());
        player->add_space(space);
        space->setOwned();
        space->setOwner(player->getId());

        qDebug() << "AFTER SELLSPACE" << QString::fromStdString(space->getInfo());

        //HACK: downcast to appropriate subclass and add it to list of
        //properties/utilities/railroads for usage in other functions
        std::string type = space->getType();
        switch (type.at(0)) {
            case 'U' :
                player->add_utility(static_cast<Utility*>(space));
            break;
            case 'P':
                player->add_property(static_cast<Property*>(space));
            break;
            case 'R':
                player->add_railroad(static_cast<Railroad*>(space));
            break;
            default:
            break;

        }
    }

}

void Bank::giveMoney(Player *player, int amount) {
	player->receive(amount);
}

void Bank::takeMoney(Player *player, int amount) {
	player->pay(amount);
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
