#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include <cstdint>
#include <string>

class Player : public Entity
{
public:
	Player(std::string name, uint16_t currentHealth,
		uint16_t maxHealth, uint16_t level, uint16_t experience,
		uint16_t attack, uint16_t defense, uint16_t expRequired,
		uint16_t location);
	virtual ~Player() override;

	uint16_t getExpRequired() const noexcept;
	uint16_t getLocation() const noexcept;

	// gain an amount of experience, returning the amount of levels gained
	bool gainExperience(uint16_t experience);

	// recover all health that was lost
	void recoverHealth() noexcept;

	// increments/decrements location, used by journey and backtrack cmds
	void journey() noexcept;
	void backtrack() noexcept;

private:
	// experience required for the next level
	uint16_t expRequired;
	// location id
	uint16_t location;
};

#endif // PLAYER_HPP
