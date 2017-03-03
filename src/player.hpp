#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdint>
#include "entity.hpp"

class Player : public Entity
{
public:
	Player(std::string nam, uint16_t chp, uint16_t mhp, uint16_t lvl,
		uint16_t exp, uint16_t atk, uint16_t def, uint16_t xpt,
		uint16_t loc);
	virtual ~Player() override;

	uint16_t xpt; // exp until next levelup
	uint16_t loc; // location id
};

#endif // PLAYER_HPP
