#include "Game.h"

#include "Level/DemoLevel.h"
#include "Level/PrintLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	demoLevel = new DemoLevel();
	printLevel = new PrintLevel(dynamic_cast<DemoLevel&>(*demoLevel));
	mainLevel = demoLevel;
}

Game::~Game()
{
	mainLevel = nullptr;
	delete demoLevel;
	delete printLevel;
}

Level* Game::LoadDemoLevel()
{
	return demoLevel;
}

void Game::ToggleLevel(const char* text)
{
	system("cls");

	if (text == "Print Level")
	{
		mainLevel = printLevel;
	}
}
