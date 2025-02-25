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
	// �� �ε�
	if (!ParseMap("../Assets/AStarMap.txt"))
	{
		std::cerr << "�� �ε��� �����߽��ϴ�.\n";
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
	// ���� ����.
	FILE* fp = nullptr;
	fopen_s(&fp, path, "r");

	if (fp)
	{
		// ù �� �б�.
		char buf[2048] = { };
		if (!fgets(buf, sizeof(buf), fp))
		{
			fclose(fp);
			return false;
		}

		// �� ������ ������ ���� �ӽ� �迭 ����.
		std::vector<std::string> lines;
		lines.reserve(mapHeight);

		// ������ ���� ��ġ.
		auto currentPosition = ftell(fp);

		// ������ ��ġ�� �̵�.
		fseek(fp, 0, SEEK_END);

		// ��ġ ����.
		auto endPosition = ftell(fp);

		// ũ�� ���.
		int size = (int)(endPosition - currentPosition);

		// rewind.
		fseek(fp, currentPosition, SEEK_SET);

		// ������ �б�.
		fread_s(buf, 2048, size, 1, fp);

		// ���� �Ľ�.
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

		// ���κ� �Ľ� ������ ����.
		std::vector<char> line;
		line.reserve(mapWidth);

		// ������ ���� nullptr ����.
		token = nullptr;

		// ���� �迭�� ��ȸ�ϸ鼭 �Ľ� ó��.
		for (auto& item : lines)
		{
			// ������ ���� nullptr ����.
			context = nullptr;

			// ù ĭ ó��.
			token = strtok_s(const_cast<char*>(item.c_str()), ",", &context);
			if (token)
			{
				line.emplace_back(token[0]);
			}

			// �� ��° ĭ���ʹ� ����.
			while (context)
			{
				token = strtok_s(nullptr, ",", &context);
				if (!token)
				{
					break;
				}
				line.emplace_back(token[0]);
			}

			// ó���� ������ ������ �ʿ� �߰�.
			map.emplace_back(line);
			line.clear();
		}

		// ���� �ݱ�.
		fclose(fp);
		return true;
	}

	return false;
}

void DemoLevel::DrawMap()
{
	if (map.empty())
	{
		std::cerr << "�� ������ ����ֽ��ϴ�.\n";
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

	// Start ��ġ ���.
	Engine::Get().Draw(Vector2(start->GetPosition().x, start->GetPosition().y), "S", Color::Green);

	// End ��ġ ���.
	Engine::Get().Draw(Vector2(end->GetPosition().x, end->GetPosition().y), "E", Color::Red);
}
