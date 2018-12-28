#include "Card.hpp"

#define NUM_CHANCE 17
#define NUM_CHEST 17

std::vector<Card*> Card::initialize_cards(){
	unsigned i = 0;
	std::vector<std::string> messages = {
		// chance messages
		"Advance to Go. (Collect $200)", 
		"Advance to Illinois Ave. If you pass Go, collect $200.",
		"Advance to St. Charles Place. If you pass Go, collect $200.", 
		"Advance token to nearest Utility. If unowned, you may buy it from the Bank. If owned, throw dice and pay owner a total 10 times the amount thrown.", 
		"Advance token to the nearest Railroad and pay owner twice the rental to which he/she is otherwise entitled. If Railroad is unowned, you may buy it from the Bank.",
		"Advance token to the nearest Railroad and pay owner twice the rental to which he/she is otherwise entitled. If Railroad is unowned, you may buy it from the Bank.", 
		"Bank pays you dividend of $50.",
		"Get out of Jail Free. This card may be kept until needed, or traded/sold.",
		"Go Back Three Spaces.",
		"Go to Jail. Go directly to Jail. Do not pass GO, do not collect $200.",
		"Make general repairs on all your property: For each house pay $25, For each hotel $100.",
		"Pay poor tax of $15.",
		"Take a trip to Reading Railroad. If you pass Go, collect $200.",
		"Take a walk on the Boardwalk. Advance token to Boardwalk.",
		"You have been elected Chairman of the Board. Pay each player $50.",
		"Your building loan matures. Receive $150.",
		"You have won a crossword competition. Collect $100.",
		// community chest messages
		"Advance to Go. (Collect $200)",
		"Bank error in your favor. Collect $200.",
		"Doctor's fees. Pay $50.",
		"From sale of stock you get $50.",
		"Get Out of Jail Free. This card may be kept until needed or sold/traded.",
		"Go to Jail. Go directly to jail. Do not pass Go, Do not collect $200.",
		"Grand Opera Night. Collect $50 from every player for opening night seats.",
		"Holiday Fund matures. Receive $100.",
		"Income tax refund. Collect $20.",
		"It is your birthday. Collect $10 from every player.",
		"Life insurance matures – Collect $100.",
		"Hospital Fees. Pay $50.",
		"School fees. Pay $50.",
		"Receive $25 consultancy fee.",
		"You are assessed for street repairs: Pay $40 per house and $115 per hotel you own.",
		"You have won second prize in a beauty contest. Collect $10.",
		"You inherit $100.",
	};
	
	std::vector<Card*> cards(NUM_CHANCE + NUM_CHEST);
	for(i=0; i<NUM_CHANCE; i++)
	{
		cards[i] = new Card("CHANCE", messages[i], i);
	}

	for(i=NUM_CHANCE; i<cards.size(); i++)
	{
		cards[i] = new Card("COMMUNITY_CHEST", messages[i], i);
	}
	
	return cards;
}
