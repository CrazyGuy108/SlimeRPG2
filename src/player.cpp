#include "player.hpp"

Player::Player(std::string name, uint16_t currentHealth,
	uint16_t maxHealth, uint16_t level, uint16_t experience,
	uint16_t attack, uint16_t defense, uint16_t expRequired,
	uint16_t location)
	: Entity{ name, currentHealth, maxHealth, level, experience, attack,
		defense },
	expRequired{ expRequired },
	location{ location }
{
}

Player::~Player()
{
}

uint16_t Player::getExpRequired() const noexcept
{
	return expRequired;
}

uint16_t Player::getLocation() const noexcept
{
	return location;
}

void Player::setExpRequired(uint16_t expRequired) noexcept
{
	this->expRequired = expRequired;
}

void Player::setLocation(uint16_t location) noexcept
{
	this->location = location;
}
