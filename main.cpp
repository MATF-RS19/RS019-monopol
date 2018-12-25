#include <vector>

#include "Card.hpp"

#define NUM_CHANCE 17

using namespace std;

void initialize_properties();
void initialize_utilities();
vector<Card*> initialize_cards();

int main(int argc, char** argv)
{
	initialize_properties();
	initialize_utilities();
	vector<Card*> cards(NUM_CHANCE);
	cards = initialize_cards();
	return 0;
}

vector<Card*> initialize_cards()
{
	int i = 0;
	vector<Card*> cards(NUM_CHANCE);
	for(i=0; i<NUM_CHANCE; i++)
	{
		cards[i] = new Card("CHANCE", "nesto");
	}
	return cards;
}

void initialize_properties()
{
	
}

void initialize_utilities()
{
	
}