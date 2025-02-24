#include "DemoLevel.h"
#include "Actor/Start.h"
#include "Actor/End.h"
#include "Engine/Engine.h"

#include <iostream>
#include <fstream>
#include <string>

DemoLevel::DemoLevel()
	: player(new Player()), start(new Start()), end(new End())
{
	// 맵 로드
	if (!ParseMap("../Assets/AStarMap.txt"))
	{
		std::cerr << "맵 로딩 실패" << std::endl;
	}
	
	AddActor(player);
	AddActor(start);
	AddActor(end);
}

void DemoLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void DemoLevel::Draw()
{
	Super::Draw();
	DrawMap();
}

bool DemoLevel::ParseMap(const char* path)
{
	FILE* fp = nullptr;
	fopen_s(&fp, path, "r");

	if (!fp)
	{
		std::cerr << "맵 파일을 열 수 없습니다.\n";
		return false;
	}

	// 기존 맵 데이터 초기화.
	map.clear();

	char buf[256];

	// 맵 데이터 해석을 위한 루프.
	while (fgets(buf, sizeof(buf), fp))
	{
		std::vector<char> line;
		char* context = nullptr;
		char* token = strtok_s(buf, ",", &context);

		while (token)
		{
			line.emplace_back(token[0]);
			token = strtok_s(nullptr, ",", &context);
		}

		// 처리된 라인 데이터를 맵에 추가.
		map.push_back(line);
	}

	fclose(fp);
	return true;
}

void DemoLevel::DrawMap()
{
	if (map.empty())
	{
		std::cerr << "맵 파일이 비어있습니다.\n";
		return;
	}

	Vector2 screenSize = Engine::Get().ScreenSize();
	int offsetX = (screenSize.x - mapWidth) / 2;
	int offsetY = (screenSize.y - mapHeight) / 2;

	for (int y = 0; y < map.size(); ++y)
	{
		for (int x = 0; x < map[y].size(); ++x)
		{
			Engine::Get().Draw(Vector2(offsetX + x, offsetY + y), std::string(1, map[y][x]).c_str(), Color::White);
		}
	}

	// Player 위치 출력.
	Engine::Get().Draw(Vector2(player->GetPosition().x, player->GetPosition().y), "P", Color::Cyan);

	// Start 위치 출력.
	Engine::Get().Draw(Vector2(start->GetPosition().x, start->GetPosition().y), "S", Color::Green);

	// End 위치 출력.
	Engine::Get().Draw(Vector2(end->GetPosition().x, end->GetPosition().y), "E", Color::Red);
}
