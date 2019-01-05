#pragma once

#include <iostream>
#include <vector>

/*
 * Interface for all of the spaces on the board. 
 * NOTE: ActionSpace class is pretty different from all of the other spaces
 *       maybe it was a bad idea to subclass the Space in both normal spaces
 *       and action spaces
 * TODO: Try to implemet everything via smart pointers
*/

class Space{

	public:
		virtual void printSpace() const = 0;

        virtual std::string getName() const = 0;
        
        virtual double getBuyPrice() const = 0;
        
        virtual void setOwned() = 0;
        
        virtual bool isOwned() const = 0;
        
        virtual void setOwner(int id) = 0;
        
        virtual int getOwner() const = 0;
        
        virtual std::string getGroup() const = 0;
        
        virtual int getNumBuildings() const = 0;
        
        virtual int getAction() const = 0;
};
