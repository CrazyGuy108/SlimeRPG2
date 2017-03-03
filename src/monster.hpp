#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "entity.hpp"
#include <cstdint>
#include <string>

class Monster : public Entity
{
public:
	Monster(std::string nam, uint16_t chp, uint16_t mhp, uint16_t lvl,
		uint16_t exp, uint16_t atk, uint16_t def, std::string msg);
	virtual ~Monster() override;

	std::string msg; // encounter message
};

#endif // MONSTER_HPP
