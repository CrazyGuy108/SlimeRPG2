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

bool Player::gainExperience(uint16_t experience)
{
	setExperience(getExperience() + experience);
	// check for levelup
	if (getExperience() >= expRequired)
	{
		// not sure if power-leveling would be even possible in this
		//  game, but if you somehow gain more than 1 level, this will
		//  take care of that
		uint16_t levelsGained{ static_cast<uint16_t>(getExperience() /
				expRequired) };
		// update stats for each level gained
		// instead of using the compound interest formula, a single
		//  loop was used instead to save time and clarity
		setExperience(getExperience() % expRequired );
		setLevel(getLevel() + levelsGained);
		for (int i = 0; i < levelsGained; ++i)
		{
			expRequired *= 1.8;
			setCurrentHealth(getCurrentHealth() * 1.4);
			setMaxHealth(getMaxHealth() * 1.4);
			setAttack(getAttack() * 1.4);
			setDefense(getDefense() * 1.4);
		}
		return true;
	}
	return false;
}

void Player::recoverHealth() noexcept
{
	setCurrentHealth(getMaxHealth());
}

void Player::journey() noexcept
{
	++location;
}

void Player::backtrack() noexcept
{
	--location;
}
