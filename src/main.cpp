#include <vector>
#include <iostream>
#include <ctime>
#include <QApplication>
#include "mainwindow.h"
#include "Board.hpp"
#include "Game.hpp"

int main(int argc, char** argv)
{
    std::srand(unsigned(std::time(0)));
    
    QApplication app(argc, argv);
    
    // Game g;
    
   
    //Board *b = new Board();
    //Board b;
    
    //Card dummyCard = b.drawCard();
    
    //std::cout << dummyCard.getMsg() << std::endl;
 	
    //b.printBoard();
    
//     Game g{2};
    //g.showBoard();
    //g.printPlayers();
/*    
    auto p = g.throwDice();
    std::cout << p.first << ", " << p.second << std::endl;*/
    
//     Board *b = g.getBoard();
//     std::vector<Space*> group = b->getSpacesByGroup("ORANGE");
//     for(auto i : group){
//         std::cout << i->getName() << "[GROUP]" << std::endl;
//     }
    
    
//     std::vector<Space*> spaces = b->getSpaces();
//     for(auto i : spaces){
//         std::cout << "[SPACE]" << i->getName() << std::endl;
//     }
     /*
    std::vector<Space*> spaces = b->getSpaces();
    for(auto i : spaces) {
        std::cout << "[SPACE]" << i->getName() << std::endl;
    }
    */
//     Space* firstt = spaces.at(1);
//     std::cout << "===============\n";
//     std::cout << b->getSpaces().at(0)->getName() << std::endl;
//     std::cout << b->getSpaces().at(2)->getName() << std::endl;
//     
//      Bank *bank = g.getBank();
//     bank->sellProperty(g.getCurrentPlayer(), static_cast<Property*>(firstt));
    
//     std::cout << static_cast<Property*>(firstt)->isOwned() << std::endl;
    
//     Player* cur = g.getCurrentPlayer();
//     std::vector<Property*> props = cur->get_properties();
//     for(auto i : props){
//         std::cout << cur->get_name() << " owns " << i->getName() << std::endl;
//     }
 /*   
    std::cout << "buildings present on" << static_cast<Property*>(spaces.at(1))->getName() << std::endl;
    std::cout << static_cast<Property*>(spaces.at(1))->getNumBuildings() << std::endl;
    //g.nextPlayer();
    Player *cur = g.getCurrentPlayer();
    std::cout << cur->get_name() << std::endl;
    
    bank->sellSpace(cur, static_cast<Property*>(spaces.at(1)));
    bank->sellSpace(cur, static_cast<Property*>(spaces.at(3)));
    g.build(cur, static_cast<Property*>(spaces.at(1)));
    g.build(cur, static_cast<Property*>(spaces.at(1)));
    */
    //std::cout << "buildings present on" << static_cast<Property*>(spaces.at(1))->getName() << std::endl;
    //std::cout << static_cast<Property*>(spaces.at(1))->getNumBuildings() << std::endl;
    
//     bank->sellProperty(cur, static_cast<Property*>(spaces.at(3)));
//     bank->sellProperty(cur, static_cast<Property*>(spaces.at(6)));
//     props = cur->get_properties();
//     for(auto i : props){
//         std::cout << cur->get_name() << " owns " << i->getName() << std::endl;
//     }
//     
//     bank->sellSpace(cur, spaces.at(8));
//     bank->sellSpace(cur, spaces.at(12));
//     std::vector<Space*> spcs = cur->get_spaces();
//     for(auto i : spcs){
//         std::cout << cur->get_name() << " owns[sellspace] " << i->getName() << std::endl;
//     }
    /*
    std::vector<Space*> spcs;
    Space* landed;
    char wait;
    while(1) {
        std::cout << cur->get_pos() << std::endl;
        std::cout << g.getCurrentPlayerSpace()->getName() << std::endl;
        auto dice = g.throwDice();
        g.movePlayer(cur,dice.first+dice.second);
        landed = g.getCurrentPlayerSpace();
        if(landed->getAction() == static_cast<int>(ActionSpace::EnumActionSpace::CHANCE)){
            Card drawed = b->drawCard();
            std::cout << "CHANCE " << drawed.getMsg() << std::endl;
            std::cin >> wait;
        }else if(landed->getAction() == static_cast<int>(ActionSpace::EnumActionSpace::COMMUNITY_CHEST)){
            Card drawed = b->drawCard();
            std::cout << "COMMUNITY_CHEST " << drawed.getMsg() << std::endl;
            std::cin >> wait;
        }
    }*/
//         char answer;
//         if(!landed->isOwned()){
//             std::cout << "Do you want to buy " << landed->getName() << " for " << landed->getBuyPrice() << "?" << std::endl;
//             std::cin >> answer;
//             if(answer == 'y'){
//                 bank->sellSpace(cur, g.getCurrentPlayerSpace());
//             }
//         }
//         spcs = cur->get_spaces();
//         for(auto i : spcs){
//             std::cout << cur->get_name() << " owns[sellspace] " << i->getName() << std::endl;
//         }
//         if(answer == 'e')
//             break;
//         
//     }
    
//     std::vector<Space*> properties = cur->get_spaces();
//     for(auto i : properties){
//             std::cout << cur->get_name() << " owns[get_spaces] " << i->getName() << std::endl;
//     }
//     Property* buildOnMe = static_cast<Property*>(properties.at(0));
//     std::cout << "buildings present on" << buildOnMe->getName() << std::endl;
//     std::cout << buildOnMe->getNumBuildings() << "owner: " << buildOnMe->getOwner() << std::endl;
//     std::cout << cur->getId() << std::endl;
//     g.build(cur,buildOnMe);
//     std::cout << "buildings present on" << buildOnMe->getName() << std::endl << buildOnMe->getNumBuildings();

    MainWindow main;
    main.show();
    return app.exec();
    
}
