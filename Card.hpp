#pragma once

#include <string>

using namespace std;

class Card
{
public:
	Card(string type, string message)
	: _type(type), _message(message)
	{}
private:
	string _type, _message;
};