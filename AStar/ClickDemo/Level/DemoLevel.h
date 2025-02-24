#pragma once

#include <vector>

#include "Level/Level.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Actor/End.h"

class DemoLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// ���� �ҷ��� �Ľ�.
	bool ParseMap(const char* path);

	// �Ľ��� ���� ���.
	void DrawMap();

private:
	Player* player = nullptr;
	Start* start = nullptr;
	End* end = nullptr;

	std::vector<std::vector<char>> map;
	int mapWidth = 40;
	int mapHeight = 25;
};
