#ifndef SLIMERPG_HPP
#define SLIMERPG_HPP

#include <string>

// gets input from user
void input(std::string& ref, const std::string& msg);

// pauses the thread for an amount of milliseconds
void sleep(unsigned milliseconds);

// displays a "..." message with each dot separated by a 1 second delay
void dotdotdot();

#endif // SLIMERPG_HPP
