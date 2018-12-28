#pragma once

#include <string>
#include <vector>

class Card
{
public:
	Card(std::string type, std::string message, int action)
	: _type(type), _message(message), m_action(action)
	{}
	
	static std::vector<Card*> initialize_cards();

    std::string getType() const{
        return _type;
    }
    
    std::string getMsg() const{
        return _message;
    }
    
 	int getAction() const{
 		return m_action;
 	}
private:
	std::string _type, _message;
	int m_action;
};
