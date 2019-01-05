#include <vector>
#include <iostream>
#include <ctime>
#include <QApplication>
#include <QString>

#include "Board.hpp"
#include "Game.hpp"
#include "mainwindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

    std::srand(unsigned(std::time(0)));
    
    // Game g;
    
   
    //Board *b = new Board();
    //Board b;
    
    //Card dummyCard = b.drawCard();
    
    //std::cout << dummyCard.getMsg() << std::endl;
 	
    //b.printBoard();
	
/* BUG: ulazi u beskonacnu petlju, pa gui ne moze lepo da se izvrsava
 
    Game g{2};
    g.showBoard();
    g.printPlayers();
    
    auto p = g.throwDice();
    std::cout << p.first << ", " << p.second << std::endl;
    
    Board *b = new Board();
    std::vector<Space*> spaces = b->getSpaces();
    Space* firstt = spaces.at(1);
    std::cout << "===============\n";
    std::cout << b->getSpaces().at(0)->getName() << std::endl;
    std::cout << b->getSpaces().at(2)->getName() << std::endl;
    
    Bank *bank = g.getBank();
    bank->sellProperty(g.getCurrentPlayer(), static_cast<Property*>(firstt));
    
    std::cout << static_cast<Property*>(firstt)->isOwned() << std::endl;
    
    Player* cur = g.getCurrentPlayer();
    std::vector<Property*> props = cur->get_properties();
    for(auto i : props){
        std::cout << cur->get_name() << " owns " << i->getName() << std::endl;
    }
    
    g.nextPlayer();
    cur = g.getCurrentPlayer();
    std::cout << cur->get_name() << std::endl;
    
    bank->sellProperty(cur, static_cast<Property*>(spaces.at(3)));
    bank->sellProperty(cur, static_cast<Property*>(spaces.at(6)));
    props = cur->get_properties();
    for(auto i : props){
        std::cout << cur->get_name() << " owns " << i->getName() << std::endl;
    }
    
    bank->sellSpace(cur, spaces.at(8));
    bank->sellSpace(cur, spaces.at(12));
    std::vector<Space*> spcs = cur->get_spaces();
    for(auto i : spcs){
        std::cout << cur->get_name() << " owns[sellspace] " << i->getName() << std::endl;
    }
    
    while(1){
        std::cout << cur->get_pos() << std::endl;
        std::cout << g.getCurrentPlayerSpace()->getName() << std::endl;
        auto dice = g.throwDice();
        std::cout << dice.first << "," << dice.second << std::endl;
        g.movePlayer(cur,dice.first+dice.second);
        Space* landed = g.getCurrentPlayerSpace();
        char answer;
        if(!landed->isOwned()){
            std::cout << "Do you want to buy " << landed->getName() << " for " << landed->getBuyPrice() << "?" << std::endl;
            std::cin >> answer;
            if(answer == 'y'){
                bank->sellSpace(cur, g.getCurrentPlayerSpace());
            }
        }
        spcs = cur->get_spaces();
        for(auto i : spcs){
            std::cout << cur->get_name() << " owns[sellspace] " << i->getName() << std::endl;
        }
        
    }
	*/
	
	MainWindow main;

	main.show();
    
	return app.exec();
}





