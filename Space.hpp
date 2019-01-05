#pragma once

#include <iostream>

class Space{

    //TODO: add this 
// 	public:
// 		// Every space should perform some kind of action when player steps on it
// 		virtual void action();

	public:
		virtual void printSpace() const = 0;
        virtual std::string getName() const = 0;
        //NOTE: malo je ruzno, ali nikada necemo koristiti funkciju u klasi u kojoj nije implementirana
        //tj. u ActionSpace klasi
        virtual double getBuyPrice() const = 0;
        virtual void setOwned() {};
        virtual bool isOwned() const = 0;
        virtual std::string getType() const = 0;
};
