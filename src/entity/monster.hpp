#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "entity.hpp"
#include <cstdint>
#include <string>

class Monster : public Entity
{
public:
	Monster(std::string name, uint16_t currentHealth,
		uint16_t maxHealth, uint16_t level, uint16_t experience,
		uint16_t attack, uint16_t defense, std::string message);
	virtual ~Monster() override;

	const std::string& getMessage() const noexcept;

private:
	std::string message;
};

#endif // MONSTER_HPP
