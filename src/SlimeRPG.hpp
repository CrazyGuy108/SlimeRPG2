#ifndef SLIMERPG_HPP
#define SLIMERPG_HPP

#include <cstdint>
#include <string>
#include <vector>

// gets input from user
void input(std::string& ref, const std::string& msg);

// pauses the thread for an amount of milliseconds
void sleep(unsigned milliseconds);

// displays a "..." message with each dot separated by a 1 second delay
void dotdotdot();

// Player struct.
struct Player
{
	std::string nam; // player name
	uint16_t chp; // current health points
	uint16_t mhp; // max Health
	uint16_t lvl; // level
	uint16_t exp; // experience
	uint16_t xpt; // exp until next levelup
	uint16_t atk; // attack
	uint16_t def; // defense
	uint16_t loc; // location id
};

// Monster struct.
struct Monster
{
	std::string nam; // monster name
	std::string msg; // encounter message
	uint16_t chp; // current health points
	uint16_t mhp; // max health
	uint16_t lvl; // level
	uint16_t exp; // experience given when killed
	uint16_t atk; // attack
	uint16_t def; // defense
};

// Location struct.
struct Location
{
	std::string nam; // location name
	uint16_t lvl; // level requirement to enter
	std::vector<Monster> thr; // list of encounterable threats
	std::vector<std::string> msg; // messages randomly displayed when recovering
	std::vector<std::string> dth; // recovery messages when you've killed every monster in the area
};

#endif // SLIMERPG_HPP
