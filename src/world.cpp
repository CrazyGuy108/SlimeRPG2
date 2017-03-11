#include "world.hpp"

World::World(std::initializer_list<Location> il)
	: locations{ il }
{
}

bool World::contains(size_t id) const noexcept
{
	return id < locations.size();
}

Location& World::getLocation(size_t id)
{
	return locations[id];
}

const Location& World::getLocation(size_t id) const
{
	return locations[id];
}
