#pragma once

#include <iostream>

class Space{

    //TODO: add this 
// 	public:
// 		// Every space should perform some kind of action when player steps on it
// 		virtual void action();

	public:
		virtual void printSpace() const = 0;
};
