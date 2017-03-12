#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include <cstdint>
#include <string>

class Location;

class Player : public Entity
{
public:
	Player(std::string name, uint16_t currentHealth,
		uint16_t maxHealth, uint16_t level, uint16_t experience,
		uint16_t attack, uint16_t defense, uint16_t expRequired,
		Location* location);
	virtual ~Player() override;

	uint16_t getExpRequired() const noexcept;
	Location* getLocation() noexcept;
	const Location* getLocation() const noexcept;
	void setLocation(Location* location) noexcept;

	// gain an amount of experience, returning the amount of levels gained
	bool gainExperience(uint16_t experience);

	// recover all health that was lost
	void recoverHealth() noexcept;

private:
	// experience required for the next level
	uint16_t expRequired;
	// location id
	Location* location;
};

#endif // PLAYER_HPP
