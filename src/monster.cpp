#include "monster.hpp"

Monster::Monster(std::string nam, uint16_t chp, uint16_t mhp, uint16_t lvl,
	uint16_t exp, uint16_t atk, uint16_t def, std::string msg)
	: Entity{ nam, chp, mhp, lvl, exp, atk, def }, msg{ msg }
{
}

Monster::~Monster()
{
}
