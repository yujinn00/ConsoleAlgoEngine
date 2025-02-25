#pragma once

#include <vector>

#include "Level/Level.h"
#include "Actor/Start.h"
#include "Actor/End.h"

class DemoLevel : public Level
{
	// RTTI Á¤ÀÇ.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// ¸ÊÀ» ºÒ·¯¿Í ÆÄ½Ì.
	bool ParseMap(const char* path);

	// ÆÄ½ÌÇÑ ¸ÊÀ» Ãâ·Â.
	void DrawMap();

	// Getter.
	Start* GetStart() const;
	End* GetEnd() const;
	std::vector<std::vector<char>>& GetMap();
	int GetMapWidth() const;
	int GetMapHeight() const;

private:
	Start* start = nullptr;
	End* end = nullptr;

	std::vector<std::vector<char>> map;
	int mapWidth = 40;
	int mapHeight = 25;
};
