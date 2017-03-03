#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "monster.hpp"

class Location
{
public:
	Location(std::string nam, uint16_t lvl, std::vector<Monster> thr,
		std::vector<std::string> msg, std::vector<std::string> dth);

	std::string nam; // location name
	uint16_t lvl; // level requirement to enter
	std::vector<Monster> thr; // list of encounterable threats
	std::vector<std::string> msg; // messages randomly displayed when recovering
	std::vector<std::string> dth; // recovery messages when you've killed every monster in the area
};

#endif // LOCATION_HPP
