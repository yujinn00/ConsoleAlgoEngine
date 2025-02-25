#pragma once

#include <vector>

#include "Level/Level.h"
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

	// Getter.
	inline Start* GetStart() const { return this->start; }
	inline End* GetEnd() const { return this->end; }
	inline std::vector<std::vector<char>>& GetMap() { return this->map; }
	inline int GetMapWidth() const { return this->mapWidth; }
	inline int GetMapHeight() const { return this->mapHeight; }

private:
	Start* start = nullptr;
	End* end = nullptr;

	std::vector<std::vector<char>> map;
	int mapWidth = 40;
	int mapHeight = 25;
};
