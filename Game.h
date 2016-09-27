#pragma once
#include "Tournament.h"
class Game
{
public:
	Game();
	// function that implements the game
	void Run();

	char Play(Tournament &t, bool firstRun);

	~Game();
};

