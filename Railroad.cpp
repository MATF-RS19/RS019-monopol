#include "Railroad.hpp"

std::vector<Railroad*> Railroad::initialize_railroads()
{
	Railroad* reading = new Railroad(200, 25, 100, "Reading railroad");
	Railroad* penn = new Railroad(200, 25, 100, "Pennsylvania Railroad");
	Railroad* bo = new Railroad(200, 25, 100, "B. & O. Railroad");
	Railroad* sl = new Railroad(200, 25, 100, "Short Line");	
	
	std::vector<Railroad*> railroads = {reading, penn, bo, sl};
	return railroads;	
}
