#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include <cstdint>

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
	void setExpRequired(uint16_t expRequired) noexcept;
	void setLocation(uint16_t location) noexcept;

private:
	// experience required for the next level
	uint16_t expRequired;
	// location id
	uint16_t location;
};

#endif // PLAYER_HPP
