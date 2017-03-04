#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "monster.hpp"
#include <cstdint>
#include <string>
#include <vector>

class Location
{
public:
	typedef std::string message_t;
	typedef std::vector<message_t> message_container_t;
	typedef std::vector<Monster> monster_container_t;
	typedef monster_container_t::iterator monster_iterator_t;

	Location(std::string name, uint16_t levelRequirement,
		monster_container_t enemies,
		message_container_t recoveryMessages,
		message_container_t killerMessages);

	message_t& getName() noexcept;
	const message_t& getName() const noexcept;
	uint16_t getLevelRequirement() const noexcept;
	bool allMonstersDead() const noexcept;
	monster_iterator_t getRandomMonster();
	const message_t& getRandomMessage() const;

	// removes an enemy using an iterator from randomEnemy()
	void removeEnemy(monster_iterator_t monster);

private:
	message_t name;
	uint16_t levelRequirement;
	monster_container_t enemies;
	message_container_t recoveryMessages;
	// recovery messages for when you've killed every monster in the area
	message_container_t killerMessages;
};

#endif // LOCATION_HPP
