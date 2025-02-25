#include <iostream>
#include <string>

#include "DemoLevel.h"
#include "Game/Game.h"
#include "Actor/Start.h"
#include "Actor/End.h"
#include "Engine/Engine.h"

DemoLevel::DemoLevel()
	: start(new Start()), end(new End())
{
	// 맵 로드
	if (!ParseMap("../Assets/AStarMap.txt"))
	{
		std::cerr << "맵 로딩에 실패했습니다.\n";
	}
	
	AddActor(start);
	AddActor(end);
}

void DemoLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if (Engine::Get().GetKeyDown(VK_RETURN))
	{
		Game::Get().ToggleLevel("Print Level");
	}
}

void DemoLevel::Draw()
{
	Super::Draw();
	DrawMap();
}

bool DemoLevel::ParseMap(const char* path)
{
	// 파일 열기.
	FILE* fp = nullptr;
	fopen_s(&fp, path, "r");

	if (fp)
	{
		// 첫 줄 읽기.
		char buf[2048] = { };
		if (!fgets(buf, sizeof(buf), fp))
		{
			fclose(fp);
			return false;
		}

		// 줄 데이터 저장을 위한 임시 배열 선언.
		std::vector<std::string> lines;
		lines.reserve(mapHeight);

		// 파일의 현재 위치.
		auto currentPosition = ftell(fp);

		// 마지막 위치로 이동.
		fseek(fp, 0, SEEK_END);

		// 위치 저장.
		auto endPosition = ftell(fp);

		// 크기 계산.
		int size = (int)(endPosition - currentPosition);

		// rewind.
		fseek(fp, currentPosition, SEEK_SET);

		// 나머지 읽기.
		fread_s(buf, 2048, size, 1, fp);

		// 라인 파싱.
		char* context = nullptr;
		char* token = strtok_s(buf, "\n", &context);
		if (token)
		{
			lines.emplace_back(token);
		}

		while (context)
		{
			token = strtok_s(nullptr, "\n", &context);
			if (!token)
			{
				break;
			}
			lines.emplace_back(token);
		}

		// 라인별 파싱 데이터 저장.
		std::vector<char> line;
		line.reserve(mapWidth);

		// 재사용을 위한 nullptr 설정.
		token = nullptr;

		// 라인 배열을 순회하면서 파싱 처리.
		for (auto& item : lines)
		{
			// 재사용을 위한 nullptr 설정.
			context = nullptr;

			// 첫 칸 처리.
			token = strtok_s(const_cast<char*>(item.c_str()), ",", &context);
			if (token)
			{
				line.emplace_back(token[0]);
			}

			// 두 번째 칸부터는 루프.
			while (context)
			{
				token = strtok_s(nullptr, ",", &context);
				if (!token)
				{
					break;
				}
				line.emplace_back(token[0]);
			}

			// 처리된 라인을 데이터 맵에 추가.
			map.emplace_back(line);
			line.clear();
		}

		// 파일 닫기.
		fclose(fp);
		return true;
	}

	return false;
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

	// Start 위치 출력.
	Engine::Get().Draw(Vector2(start->GetPosition().x, start->GetPosition().y), "S", Color::Green);

	// End 위치 출력.
	Engine::Get().Draw(Vector2(end->GetPosition().x, end->GetPosition().y), "E", Color::Red);
}
