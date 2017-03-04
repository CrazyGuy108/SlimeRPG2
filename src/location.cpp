#include "location.hpp"

Location::Location(std::string name, uint16_t levelRequirement,
	std::vector<Monster> enemies,
	std::vector<std::string> recoveryMessages,
	std::vector<std::string> killerMessages)
	: name{ name }, levelRequirement{ levelRequirement },
	enemies{ enemies }, recoveryMessages{ recoveryMessages },
	killerMessages{ killerMessages }
{
}

std::string& Location::getName() noexcept
{
	return name;
}

const std::string& Location::getName() const noexcept
{
	return name;
}

uint16_t Location::getLevelRequirement() const noexcept
{
	return levelRequirement;
}

std::vector<Monster>& Location::getEnemies() noexcept
{
	return enemies;
}

const std::vector<Monster>& Location::getEnemies() const noexcept
{
	return enemies;
}

const std::vector<std::string>& Location::getRecoveryMessages() const noexcept
{
	if (allMonstersDead())
	{
		return killerMessages;
	}
	return recoveryMessages;
}

bool Location::allMonstersDead() const noexcept
{
	return enemies.empty();
}

void Location::removeEnemy(size_t index)
{
	enemies.erase(enemies.begin() + index);
}
