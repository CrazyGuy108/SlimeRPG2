#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>

class Monster;
class Player;
class World;

class Game
{
public:
	Game(Player& player, World& world);

	void start();

private:
	enum class State;

	// parses and executes a command
	void execute(const std::string& cmd);

	// commands
	void help();
	void stats();
	void fight();
	void flee();
	void rest();
	void travel();
	void leave();

	// helper methods
	void battle();
	void winBattle();
	void loseBattle();
	void travelTo(size_t location);
	void dotdotdot();
	void sleep(unsigned milliseconds);

	Player& player;
	World& world;
	Monster* monster;
	size_t monsterId;
	State state;
};

#endif // GAME_HPP
