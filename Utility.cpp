#include "Utility.hpp"

void Utility::printSpace() const{

	std::cout << "Utility: " << Utility::getGroup() << ", price: " << Utility::getBuyPrice() << std::endl; 

}

std::vector<Utility*> Utility::initialize_utilities()
{
	Utility* water_works = new Utility(150, 75, "WATER_WORKS");
	Utility* electric_company = new Utility(150, 75, "ELECTRIC_COMPANY");
	std::vector<Utility*> utilities = {water_works, electric_company};
	return utilities;
}
