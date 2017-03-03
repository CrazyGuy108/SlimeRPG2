#include "entity.hpp"

Entity::Entity(std::string nam, uint16_t chp, uint16_t mhp, uint16_t lvl,
	uint16_t exp, uint16_t atk, uint16_t def)
	: nam{ nam }, chp{ chp }, mhp{ mhp }, lvl{ lvl }, exp{ exp },
		atk{ atk }, def{ def }
{
}

Entity::~Entity()
{
}
