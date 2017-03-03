#include "entity.hpp"
#include <utility>

Entity::Entity(std::string name, uint16_t currentHealth,
	uint16_t maxHealth, uint16_t level, uint16_t experience,
	uint16_t attack, uint16_t defense)
	: name{ name }, currentHealth{ currentHealth }, maxHealth{ maxHealth },
	level{ level }, experience{ experience }, attack{ attack },
	defense{ defense }
{
}

Entity::~Entity()
{
}

std::string& Entity::getName() noexcept
{
	return name;
}

const std::string& Entity::getName() const noexcept
{
	return name;
}

uint16_t Entity::getCurrentHealth() const noexcept
{
	return currentHealth;
}

uint16_t Entity::getMaxHealth() const noexcept
{
	return maxHealth;
}

uint16_t Entity::getLevel() const noexcept
{
	return level;
}

uint16_t Entity::getExperience() const noexcept
{
	return experience;
}

uint16_t Entity::getAttack() const noexcept
{
	return attack;
}

uint16_t Entity::getDefense() const noexcept
{
	return defense;
}

void Entity::setName(const std::string& name)
{
	this->name = name;
}

void Entity::setName(std::string&& name) noexcept
{
	this->name = std::move(name);
}

void Entity::setCurrentHealth(uint16_t currentHealth) noexcept
{
	this->currentHealth = currentHealth;
}

void Entity::setMaxHealth(uint16_t maxHealth) noexcept
{
	this->maxHealth = maxHealth;
}

void Entity::setLevel(uint16_t level) noexcept
{
	this->level = level;
}

void Entity::setExperience(uint16_t experience) noexcept
{
	this->experience = experience;
}

void Entity::setAttack(uint16_t attack) noexcept
{
	this->attack = attack;
}

void Entity::setDefense(uint16_t defense) noexcept
{
	this->defense = defense;
}
