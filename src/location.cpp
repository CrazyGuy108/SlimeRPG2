#include "location.hpp"
#include <cstdlib>
#include <iterator>

Location::Location(message_t name, uint16_t levelRequirement,
	monster_container_t enemies,
	message_container_t recoveryMessages,
	message_container_t killerMessages)
	: name{ name }, levelRequirement{ levelRequirement },
	enemies{ enemies }, recoveryMessages{ recoveryMessages },
	killerMessages{ killerMessages }
{
}

Location::message_t& Location::getName() noexcept
{
	return name;
}

const Location::message_t& Location::getName() const noexcept
{
	return name;
}

uint16_t Location::getLevelRequirement() const noexcept
{
	return levelRequirement;
}

bool Location::allMonstersDead() const noexcept
{
	return enemies.empty();
}

size_t Location::getRandomMonsterId()
{
	return rand() % enemies.size();
}

Monster* Location::getMonster(size_t id)
{
	if (allMonstersDead())
	{
		return nullptr;
	}
	return &enemies[id];
}

const Monster* Location::getMonster(size_t id) const
{
	if (allMonstersDead())
	{
		return nullptr;
	}
	return &enemies[id];
}

const Location::message_t& Location::getRandomMessage() const
{
	// choose a message container based on if all the monsters are dead
	const message_container_t& c{
		allMonstersDead() && !killerMessages.empty() ?
		killerMessages : recoveryMessages };
	// default message if that container is empty
	if (c.empty())
	{
		static const message_t defaultMessage{ "This location seems "
			"to have an air of mystery around it..." };
		return defaultMessage;
	}
	return c[rand() % c.size()];
}

void Location::removeEnemy(size_t id)
{
	enemies.erase(std::next(enemies.begin(), id));
}

