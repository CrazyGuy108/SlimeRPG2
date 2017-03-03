#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "monster.hpp"
#include <cstdint>
#include <string>
#include <vector>

class Location
{
public:
	Location(std::string name, uint16_t levelRequirement,
		std::vector<Monster> enemies,
		std::vector<std::string> recoveryMessages,
		std::vector<std::string> killerMessages);

	std::string& getName() noexcept;
	const std::string& getName() const noexcept;
	uint16_t getLevelRequirement() const noexcept;
	std::vector<Monster>& getEnemies() noexcept;
	const std::vector<Monster>& getEnemies() const noexcept;
	const std::vector<std::string>& getRecoveryMessages() const noexcept;
	const std::vector<std::string>& getKillerMessages() const noexcept;

private:
	std::string name;
	uint16_t levelRequirement;
	std::vector<Monster> enemies;
	std::vector<std::string> recoveryMessages;
	// recovery messages for when you've killed every monster in the area
	std::vector<std::string> killerMessages;
};

#endif // LOCATION_HPP
