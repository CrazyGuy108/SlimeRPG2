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

Location::monster_iterator_t Location::getRandomMonster()
{
	if (allMonstersDead())
	{
		return enemies.end();
	}
	return std::next(enemies.begin(),
		rand() % enemies.size());
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

void Location::removeEnemy(monster_iterator_t monster)
{
	enemies.erase(monster);
}

