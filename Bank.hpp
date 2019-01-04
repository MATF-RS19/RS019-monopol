#pragma once

#include "AuctionHouse.hpp"
#include "Player.hpp"
#include "Property.hpp"
#include "Utility.hpp"
#include "Railroad.hpp"

class Bank{
  
public:

    Bank();
    
    void sellProperty(Player *player, Property *property);

    void sellSpace(Player *player, Space *space);
    
private:
    
    //AuctionHouse* m_auction_house;
    //hotels and houses
    int m_houses = 32, m_hotels = 12;
    
};
