#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstdint>
#include <string>

// abstract base class for all entities
class Entity
{
public:
	Entity(std::string nam, uint16_t chp, uint16_t mhp, uint16_t lvl,
		uint16_t exp, uint16_t atk, uint16_t def);
	virtual ~Entity() = 0;

	std::string nam; // name
	uint16_t chp; // current health points
	uint16_t mhp; // max health
	uint16_t lvl; // level
	uint16_t exp; // experience
	uint16_t atk; // attack
	uint16_t def; // defense
};

#endif // ENTITY_HPP
