#ifndef WORLD_HPP
#define WORLD_HPP

#include "location.hpp"
#include <initializer_list>
#include <vector>

class World
{
public:
	World(std::initializer_list<Location> il);

	bool contains(size_t id) const noexcept;
	Location& getLocation(size_t id);
	const Location& getLocation(size_t id) const;

private:
	std::vector<Location> locations;
};

#endif // WORLD_HPP
