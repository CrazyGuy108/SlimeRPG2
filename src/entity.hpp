#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstdint>
#include <string>

// abstract base class for all entities
class Entity
{
public:
	Entity(std::string name, uint16_t currentHealth,
		uint16_t maxHealth, uint16_t level, uint16_t experience,
		uint16_t attack, uint16_t defense);
	virtual ~Entity() = 0;

	std::string& getName() noexcept;
	const std::string& getName() const noexcept;
	uint16_t getCurrentHealth() const noexcept;
	uint16_t getMaxHealth() const noexcept;
	uint16_t getLevel() const noexcept;
	uint16_t getExperience() const noexcept;
	uint16_t getAttack() const noexcept;
	uint16_t getDefense() const noexcept;
	bool isRoasted() const noexcept;
	bool isDead() const noexcept;
	void setName(const std::string& name);
	void setName(std::string&& name) noexcept;
	void setRoasted(bool roasted) noexcept;

	// damages another entity
	uint16_t damage(Entity& other);

protected:
	void setCurrentHealth(uint16_t currentHealth) noexcept;
	void setMaxHealth(uint16_t maxHealth) noexcept;
	void setLevel(uint16_t level) noexcept;
	void setExperience(uint16_t experience) noexcept;
	void setAttack(uint16_t attack) noexcept;
	void setDefense(uint16_t defense) noexcept;

private:
	std::string name;
	uint16_t currentHealth;
	uint16_t maxHealth;
	uint16_t level;
	uint16_t experience;
	uint16_t attack;
	uint16_t defense;
	bool roasted;
};

#endif // ENTITY_HPP
