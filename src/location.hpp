#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "entity/monster.hpp"
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

class Location
{
public:
	typedef std::string message_t;
	typedef std::vector<message_t> message_container_t;
	typedef std::vector<Monster> monster_container_t;

	Location(std::string name, uint16_t levelRequirement,
		monster_container_t enemies,
		message_container_t recoveryMessages,
		message_container_t killerMessages,
		std::initializer_list<size_t> exits);

	message_t& getName() noexcept;
	const message_t& getName() const noexcept;
	uint16_t getLevelRequirement() const noexcept;
	bool allMonstersDead() const noexcept;
	size_t getRandomMonsterId();
	Monster* getMonster(size_t id);
	const Monster* getMonster(size_t id) const;
	const message_t& getRandomMessage() const;
	std::vector<size_t>& getExits() noexcept;
	const std::vector<size_t>& getExits() const noexcept;

	// removes an enemy using a monster id
	void removeEnemy(size_t id);

private:
	message_t name;
	uint16_t levelRequirement;
	monster_container_t enemies;
	message_container_t recoveryMessages;
	// recovery messages for when you've killed every monster in the area
	message_container_t killerMessages;
	// holds location indexes for where you can travel to from here
	std::vector<size_t> exits;
};

#endif // LOCATION_HPP
