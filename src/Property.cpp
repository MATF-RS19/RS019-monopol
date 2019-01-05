#include "Property.hpp"

#define NUM_PROPS 22

void Property::printSpace() const{

	std::cout << "Property: " << Property::getName() << ", price: " << Property::getBuyPrice() << std::endl;

}


std::vector<Property*> Property::initialize_properties(){
	Property* p1 = new Property(60, 2, 10, 30, 90, 160, 250, 30, 50, "Mediterranean Avenue", "PURPLE");
	Property* p2 = new Property(60, 4, 20, 60, 180, 320, 450, 30, 50, "Baltic Avenue", "PURPLE");
	Property* p3 = new Property(100, 6, 30, 90, 270, 400, 550, 50, 50, "Oriental Avenue", "L_BLUE");	
	Property* p4 = new Property(100, 6, 30, 90, 270, 400, 550, 50, 50, "Vermont Avenue", "L_BLUE");
	Property* p5 = new Property(120, 8, 40, 100, 300, 450, 600, 60, 50, "Connecticut Avenue", "L_BLUE");
	Property* p6 = new Property(140, 10, 50, 150, 450, 625, 750, 70, 100, "St. Charles Place", "PINK");
	Property* p7 = new Property(140, 10, 50, 150, 450, 625, 750, 70, 100, "States Avenue", "PINK");
	Property* p8 = new Property(160, 12, 60, 180, 500, 700, 900, 80, 100, "Virginia Avenue", "PINK");
	Property* p9 = new Property(180, 14, 70, 200, 550, 750, 950, 90, 100, "St. James Place", "ORANGE");
	Property* p10 = new Property(180, 14, 70, 200, 550, 750, 950, 90, 100, "Tennessee Avenue", "ORANGE");
	Property* p11 = new Property(200, 16, 80, 220, 600, 800, 1000, 100, 100, "New York Avenue", "ORANGE");
	Property* p12 = new Property(220, 18, 90, 250, 700, 875, 1050, 110, 150, "Kentucky Avenue", "RED");
	Property* p13 = new Property(220, 18, 90, 250, 700, 875, 1050, 110, 150, "Indiana Avenue", "RED");
	Property* p14 = new Property(240, 20, 100, 300, 750, 925, 1100, 120, 150, "Illinois Avenue", "RED");
	Property* p15 = new Property(260, 22, 110, 330, 800, 975, 1150, 130, 150, "Atlantic Avenue", "YELLOW");
	Property* p16 = new Property(260, 22, 110, 330, 800, 975, 1150, 130, 150, "Ventnor Avenue", "YELLOW");
	Property* p17 = new Property(280, 24, 120, 360, 850, 1025, 1200, 140, 150, "Marvin Gardens", "YELLOW");
	Property* p18 = new Property(300, 26, 130, 390, 900, 1100, 1275, 150, 200, "Pacific Avenue", "GREEN");
	Property* p19 = new Property(300, 26, 130, 390, 900, 1100, 1275, 150, 200, "North Carolina Avenue", "GREEN");
	Property* p20 = new Property(320, 28, 150, 450, 1000, 1200, 1400, 160, 200, "Pennsylvania Avenue", "GREEN");
	Property* p21 = new Property(350, 35, 175, 500, 1100, 1300, 1500, 175, 200, "Park Place", "D_BLUE");
	Property* p22 = new Property(400, 50, 200, 600, 1400, 1700, 2000, 200, 200, "Boardwalk", "D_BLUE");
	
	std::vector<Property*> properties = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22};
	// brisanje promenljivih?
	return properties;
}
