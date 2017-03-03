#include "location.hpp"

Location::Location(std::string nam, uint16_t lvl, std::vector<Monster> thr,
	std::vector<std::string> msg, std::vector<std::string> dth);
	: nam{ nam }, lvl{ lvl }, thr{ thr }, msg{ msg }, dth{ dth }
{
}
