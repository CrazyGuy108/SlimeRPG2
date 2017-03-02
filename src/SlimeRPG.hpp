#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>



// Gets input from user.
inline void input(std::string &ref, const std::string &msg)
{
	std::cout << msg;
	std::getline(std::cin, ref);
}

// Pauses the thread for an amount of milliseconds.
inline void sleep(const unsigned milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// A "..." with each dot separated by a 1 second delay to simulate waiting for something.
inline void dotdotdot()
{
	std::cout << '.';
	sleep(1000);

	std::cout << '.';
	sleep(1000);

	std::cout << '.';
	sleep(1000);

	std::cout << '\n';
}



// Player struct.
struct Player
{
	std::string
		nam; // Player name.

	uint16_t
		chp, // Current Health Points.
		mhp, // Max Health.
		lvl, // Level.
		exp, // Experience.
		xpt, // Exp until next levelup.
		atk, // Attack.
		def, // Defense.
		loc; // Location ID.
};

// Monster struct.
struct Monster
{
	std::string
		nam, // Monster name.
		msg; // Encounter message.

	uint16_t
		chp, // Current Health Points.
		mhp, // Max Health.
		lvl, // Level.
		exp, // Experience given.
		atk, // Attack.
		def; // Defense.
};

// Location struct.
struct Location
{
	std::string
		nam; // Location name.

	uint16_t
		lvl; // Level requirement.

	std::vector<Monster>
		thr; // List of encounterable threats.

	std::vector<std::string>
		msg, // Messages randomly displayed when recovering.
		dth; // Recovery messages when you've killed every monster in the area.
};