#include "SlimeRPG.hpp"



// Player object.
Player player;

// Pointer to the monster the player is battling.
// It's a pointer because a reference has to be initialized.
// Lazy I know.
Monster *encounterPtr{ nullptr };

// Vector index for the encountered monster. Used in removing the monster when it dies.
uint8_t encounterIndex;



int main()
{
	std::cout << "Loading...\n";
	dotdotdot();
	/// Initialize the player object, monster list, and location list.

	// Initialize the rest of the player object.
	player.chp = 10;
	player.mhp = 10;
	player.lvl = 1;
	player.exp = 0;
	player.xpt = 10;
	player.atk = 5;
	player.def = 5;
	player.loc = 0;

	// Initialize list of monsters.
	std::vector<Monster> monsters
	{
		// Format: nam, msg, chp, mhp, lvl, exp, atk, def
		Monster{ "Green Slime", "A green Slime appeared!\n",							   5, 5, 1, 4, 3, 3 },
		Monster{ "Blue Slime",  "A blue Slime appears to avenge its little brother...\n",  8, 8, 2, 6, 5, 5 },
		Monster{ "Red Slime",	"A Slime, red with fury, approaches you\n",				   10, 10, 3, 8, 25, 0 },
		Monster{ "Yellow Slime", "A matured, yellow Slime confronts you\n",				   16, 16, 4, 10, 3, 10 },
		Monster{ "Ghost Slime",	"The ghost of your victims appears...\n",				   65535, 65535, 65535, 65535, 65535, 65535 } // Haha getrekt scrub.
	};

	// Initialize list of locations.
	std::vector<Location> locations
	{
		// Format: nam, lvl, thr, msg, dth

		Location
		{
			"Slime Breeding Grounds", 1,
			{ monsters[0], monsters[0], monsters[0] }, // 3 individual encounterable Green Slimes.
			{ // Messages randomly displayed when recovering.
				"Slimes, in their infancy, are green-colored, frolicking in the fields\n",
				"A bright green slime approaches you and asks, \"Mama?\"\n",
				"Some older green slimes seem to have a blue-ish tint to them\n"
			},
			{ // Messages when you've killed every monster here.
				"You don't see as much slimes here...\n",
				"Many slimes are living in fear now that their youthful generation is dead\n"
			}
		},

		Location	// If you kill or injure a monster, it stays dead/injured.
		{			// So you can essentially fight it again when you recover.
			"Path of Slime", 2,
			{ monsters[0], monsters[1], monsters[1] },
			{
				"You observe a group of blue-tinted green slimes mature into a complete blue\n",
				"Some younger green slimes follow their older blue friends, though still immature\n"
			},
			{
				"A golden flower seems to be judging you for your sins...\n",
				"A group of slimes seem to be talking about \"He\"...\n"
			}
		},

		Location
		{
			"Forest of Slime", 3,
			{ monsters[2], monsters[2], monsters[2], monsters[1], monsters[0] },
			{
				"If a slime harbors anger for too long, it starts to acquire a red-ish tint\n",
				"An old rivalry of two slimes have turned them blood red with chronic hostility\n"
			},
			{
				"You observe a slime feeling triumphant now that its rival is dead for no reason\n",
				"It looks like that golden flower is talking to you...\n"
			}
		},

		Location
		{
			"Slime Boot Camp", 4,
			{ monsters[3], monsters[3], monsters[3], monsters[3], monsters[2], monsters[1], monsters[1] },
			{
				"You observe matured yellow slimes training with some kind of slime weapon...\n",
				"It seems that blue slimes aren't actually mature, but more of a teenager\n"
			},
			{
				"A slime bullet flies past you. It seems that you are being hunted...\n",
				"You see a jar of peanut butter under a cardboard box held up by a stick\n"
			},
		},

		Location
		{
			"Slime Cemetery", 5,
			{ monsters[4] },
			{
				"A funeral is taking place. You see dried slime being dumped into a grave\n",
				"How does a slime cry? I don't even know what I saw...\n",
				"Was that a ghost moaning just now?\n"
			},
			{
				"Wait you killed the ghost slime? Wow. Gg you dirty hacker...\n"
			}
		}
	};

	// Vector list corresponding with locations, flagging them as still having monsters or not. Changes recovery messages.
	std::vector<bool> death{ false, false, false, false, false };

	// String to be used as the command input.
	std::string cmd;

	// Used to check if the player is battling, so the command loop will change the command options and whatever else.
	bool battling{ false };

	// Get player name to finish loading the game.
	input(player.nam, "Done!\nWhat is your name?\n\n");



	/// Start up the command loop.

	std::cout << "\nType \"hlp\" for a list of commands\n";

	// Command loop.
	while (true)
	{
		// Re-initialize random number generator every iteration to maximize randomness.
		srand(time(NULL));

		// Command input.
		input(cmd, "\n");

		// Line break for clarity.
		std::cout << '\n';

		// If/elseif chain to identify command.
		if (cmd == "hlp") // Help.
		{
			if (battling) // Battle help message.
			{
				std::cout
					<< "hlp - Help.....List available commands\n"
					<< "sts - Stats....List the stats of your character and the monster\n"
					<< "fgt - Fight....*Chants* fite fite fite fite fite\n"
					<< "fle - Flee.....Only nubs flee, like you...\n";
			}
			else // Regular help message.
			{
				std::cout
					<< "hlp - Help........List available commands\n"
					<< "sts - Stats.......List the stats of your character\n"
					<< "rec - Recover.....Treat your wounds and rest, observing the scenery\n"
					<< "fgt - Fight.......Engage in battle with a nearby monster\n"
					<< "jrn - Journey.....Go forward to the next area\n"
					<< "bkt - Backtrack...Revisit the location you were just at\n"
					<< "lev - Leave.......Going so soon? Fine, but you can't save! >:D\n";
			}
		}
		else
			if (cmd == "sts") // Stats.
			{
				std::cout
					<< "nam..." << player.nam << '\n'
					<< "hp...." << player.chp << '/' << player.mhp << '\n'
					<< "lvl..." << player.lvl << '\n'
					<< "exp..." << player.exp << '\n'
					<< "xpt..." << player.xpt << '\n'
					<< "atk..." << player.atk << '\n'
					<< "def..." << player.def << '\n'
					<< "loc..." << locations[player.loc].nam << '\n';

				if (battling) // Also lists monster stats if battling.
				{
					std::cout << '\n'
						<< "Monster\n"
						<< "nam..." << encounterPtr->nam << '\n'
						<< "hp...." << encounterPtr->chp << '/' << encounterPtr->mhp << '\n'
						<< "lvl..." << encounterPtr->lvl
						<< (encounterPtr->lvl == 65535 ? "\nGetrekt nub\n" : "\n");
				}
			}
			else
				if (cmd == "fgt") // Fight.
				{
					if (battling) // Fights the monster if battling already.
					{
						/// Player's turn.

						// Used in calculating damage.
						uint16_t dmg{ 1 };

						// Special dialogue flags.
						bool playerInsulted{ false }, monsterInsulted{ false };

						// Current implemented damage formula: dmg = player.atk - monster.def

						// Checks if the dmg calculation would result in anything at most 1.
						if (player.atk - encounterPtr->def <= 1)
						{
							// If so, damage stays as 1, and the monster reminds the player that they should gitgud.
							std::cout << "You only did 1 damage...\n" << encounterPtr->nam << ": Gitgud nub >->\n";

							// That scrub just dissed you, man.
							playerInsulted = true;
						}
						else // If not, then damage goes as normally. The program now needs to check if the damage would kill the monster.
						{
							dmg = player.atk - encounterPtr->def;

							std::cout << "You did " << dmg << " damage to the slime!\n";
						}

						// Checks if the damage would kill the monster.
						if (dmg >= encounterPtr->chp)
						{
							// Dead monster now. Good riddance.
							encounterPtr->chp = 0;

							// Monster death message.
							std::cout << "You mercilessly slaughtered the slime!\nYou feel like a terrible person...\n";

							// Special dialogue for if the monster insulted you before.
							if (playerInsulted)
							{
								std::cout << player.nam << ": Who's the nub now? >->\n";
							}

							// Exp gain.
							std::cout << "You gained " << encounterPtr->exp << " exp!\n";

							player.exp += encounterPtr->exp;

							// Checks for levelup.
							if (player.exp >= player.xpt)
							{
								std::cout << "You levelled up to level " << ++player.lvl << "!\n";

								// Calculates next stats.
								// XPT increases by 80%, other stats by 40%.
								player.chp *= 1.4;
								player.mhp *= 1.4;
								player.exp -= player.xpt;
								player.xpt *= 1.8;
								player.atk *= 1.4;
								player.def *= 1.4;

								// Compound interest formulas:
								// Xpt = 10(1.8^(lvl-1))
								// Hp = 10(1.4^(lvl-1))
								// Atk/def = 5(1.4^(lvl-1))
							}

							// Remove monster from location's thr vector.
							locations[player.loc].thr.erase(locations[player.loc].thr.begin() + encounterIndex);

							// Checks if the monster just deleted was the last...
							if (locations[player.loc].thr.size() == 0)
							{
								// Flags the location in the death list so recovery observations change.
								death[player.loc] = true;
							}

							// The battle is now over.
							battling = false;

							// No need to process the monster's next turn. It's already dead!
							// Jumps back to the top of the command loop.
							continue;
						}
						else // Monster survives the hit.
						{
							// Deducts damage from monster hp.
							encounterPtr->chp -= dmg;
						}

						dmg = 1;

						/// Now that you've taken your turn, it's the monster's turn now. Be afraid, very afraid...

						// Checks if the dmg calculation would result in a negative number or 0.
						if (encounterPtr->atk <= player.def)
						{
							// If so, damage stays as is, and the player reminds the monster that they should gitgud.
							std::cout << "The " << encounterPtr->nam << " did only did 1 damage...\n" << player.nam << ": Gitgud scrub >->\n";

							// Oooh you just dissed that monster.
							monsterInsulted = true;
						}
						else // If not, then damage goes as normally. The program now needs to check if the damage would kill the player.
						{
							// Shorthand check for if fighting ghost slime. If so, fixed 65535 damage for the lulz.
							dmg = (encounterPtr->lvl == 65535) ? 65535 : encounterPtr->atk - player.def;

							std::cout << encounterPtr->nam << " did " << dmg << " damage to you!\n";
						}

						// Checks if the damage would kill the monster.
						if (dmg >= player.chp)
						{
							// Gg scrub.
							player.chp = 0;

							// Player death message.
							std::cout << encounterPtr->nam << " has killed you! Looks like you got a taste of your own medicine...\n";

							// Special dialogue for fighting ghost slime.
							if (encounterPtr->lvl == 65535)
							{
								std::cout << "Gg scrub\n";
							}

							// Special dialogue for if the player insulted it before.
							if (monsterInsulted)
							{
								std::cout << encounterPtr->nam << ": Who's the scrub now? >->\n";
							}

							// Line break for clarity.
							std::cout << '\n';

							// Terminates the command loop because you are DEAD, you dirty, soulless little scrub.
							break;
						}
						else // Lucky player survives the hit.
						{
							// Deducts damage from player hp.
							player.chp -= dmg;
						}
					}
					else // If not already battling, attempt to initiate an encounter.
					{
						std::cout << "You look around for a slime to fight\n";

						dotdotdot();

						// If death list has this location flagged, that indicates no monsters are present, and never will be...
						if (death[player.loc])
						{
							std::cout << "But no slimes appear, and you have a feeling that none ever will\nHe's coming for you. Run...\n";
						}
						else
						{
							// Randomly select a monster from the current location's list of monsters.
							encounterIndex = rand() % locations[player.loc].thr.size();

							// Set encounterPtr to the randomly selected monster's address.
							encounterPtr = &locations[player.loc].thr[encounterIndex];

							// Plays the monster's encounter message.
							std::cout << encounterPtr->msg;

							// Command loop changes its command options to battle the encountered monster.
							battling = true;
						}
					}
				}
				else
					if (cmd == "fle" && battling) // Flee. Only works inside battles.
					{
						std::cout << "You fled from the fight YOU started!\nPick your fights more carefully, coward...\n";
						battling = false;
					}
					else
						if (cmd == "rec" && !battling) // Recover. Only works outside of battles.
						{
							std::cout << "You rest and treat your wounds\n";

							dotdotdot();

							// Player's current HP now back to max.
							player.chp = player.mhp;

							std::cout << "Fully recovered, you observe your surroundings\n";

							// Changes recovery message when randomly selecting.
							if (death[player.loc])
							{
								// Randomly select a location death message.
								std::cout << locations[player.loc].dth[rand() % locations[player.loc].dth.size()];
							}
							else
							{
								// Randomly select a location message.
								std::cout << locations[player.loc].msg[rand() % locations[player.loc].msg.size()];
							}

						}
						else
							if (cmd == "jrn" && !battling) // Journey. Only works outside of battles.
							{
								std::cout << "You set off to the next area, with dried slime on your hands...\n";

								dotdotdot();

								// Checks if the location's level requirement is higher than the player's level.
								if (locations.at(player.loc + 1).lvl > player.lvl)
								{
									std::cout << "You realize that the slimes there are too strong for you\nYou turn back\n";
								}
								else
								{
									// Next location.
									++player.loc;

									// At() will crash the program if beyond the vector's range. Any controlled location change does this.
									std::cout << "You arrive at the " << locations.at(player.loc).nam << ". Your slaughter continues\n";
								}
							}
							else
								if (cmd == "bkt" && !battling) // Backtrack. Only works outside of battles.
								{
									std::cout << "You retrace your steps to look for any stragglers...\n";

									dotdotdot();

									// Previous location.
									--player.loc;

									std::cout << "You arrive at " << locations.at(player.loc).nam << ". Your search resumes\n";
								}
								else
									if (cmd == "lev" && !battling) // Leave. Only works outside of battles.
									{
										break;
									}
									else
									{
										std::cout << "Invalid command!\n";
									}
	}



	/// End the program, returning 0 as normally.

	return 0;
}