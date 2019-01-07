#pragma once

#include "AuctionHouse.hpp"
#include "Player.hpp"
#include "Property.hpp"
#include "Utility.hpp"
#include "Railroad.hpp"

namespace {
   int const num_of_houses = 32;
   int const num_of_hotels = 12;
};

class Bank{
  
public:
    Bank();

    void sellSpace(Player *player, Space *space);
    void sellHouse(Player *player);
    int getHouses() const;
    void setHouses(int num);
    int getHotels() const;
    void setHotels(int num);
private:
    AuctionHouse* m_auction_house;
    int m_houses = num_of_houses, m_hotels = num_of_hotels;
};
