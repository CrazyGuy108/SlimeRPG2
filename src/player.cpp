#include "player.hpp"

Player::Player(std::string nam, uint16_t chp, uint16_t mhp, uint16_t lvl,
	uint16_t exp, uint16_t atk, uint16_t def, uint16_t xpt,
	uint16_t loc)
	: Entity{ nam, chp, mhp, lvl, exp, atk, def }, xpt{ xpt }, loc{ loc }
{
}

Player::~Player()
{
}
