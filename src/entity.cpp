#include "entity.hpp"
#include <algorithm>
#include <cstdlib>
#include <utility>

Entity::Entity(std::string name, uint16_t currentHealth,
	uint16_t maxHealth, uint16_t level, uint16_t experience,
	uint16_t attack, uint16_t defense)
	: name{ name }, currentHealth{ currentHealth }, maxHealth{ maxHealth },
	level{ level }, experience{ experience }, attack{ attack },
	defense{ defense }, roasted{ false }
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

bool Entity::isDead() const noexcept
{
	return currentHealth == 0;
}

bool Entity::isRoasted() const noexcept
{
	return roasted;
}

void Entity::setName(const std::string& name)
{
	this->name = name;
}

void Entity::setName(std::string&& name) noexcept
{
	this->name = std::move(name);
}

void Entity::setRoasted(bool roasted) noexcept
{
	this->roasted = roasted;
}

uint16_t Entity::damage(Entity& other)
{
	// current damage formula: attack - defense
	uint16_t dmg{ static_cast<uint16_t>(attack - other.defense) };
	// must be within the range [1, other.currentHealth] inclusive
	// line breaks and tabs added for clarity
	dmg = std::min<uint16_t>(
		std::max<uint16_t>(
			dmg <= attack ? dmg : 0, // prevents unsigned wrapping
			1),
		other.currentHealth);
	// apply the damage
	other.currentHealth -= dmg;
	return dmg;
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
