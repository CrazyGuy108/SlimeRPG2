#include "monster.hpp"

Monster::Monster(std::string name, uint16_t currentHealth,
	uint16_t maxHealth, uint16_t level, uint16_t experience,
	uint16_t attack, uint16_t defense, std::string message)
	: Entity{ name, currentHealth, maxHealth, level, experience, attack,
		defense },
	message{ message }
{
}

Monster::~Monster()
{
}

const std::string& Monster::getMessage() const noexcept
{
	return message;
}
