#pragma once

#include "Engine/Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	Level* LoadDemoLevel();

	void ToggleLevel(const char* text);

	static Game& Get() { return *instance; }

private:
	Level* demoLevel = nullptr;
	Level* printLevel = nullptr;

private:
	static Game* instance;
};
