#include "Start.h"
#include "Engine/Engine.h"
#include "Level/DemoLevel.h"
#include "Game/Game.h"

Start::Start(DemoLevel& demoLevel)
	: DrawableActor("S"), demoLevel(demoLevel)
{
	color = Color::Red;
	position = Vector2(5, 3);
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		Vector2 startPosition = Engine::Get().MousePosition();
		if (startPosition.x < 1 || startPosition.x > demoLevel.GetMapWidth() - 2 || startPosition.y < 1 || startPosition.y > demoLevel.GetMapHeight() - 2)
		{
			return;
		}
		if (demoLevel.GetMap()[startPosition.y][startPosition.x] == '#')
		{
			return;
		}
		position = startPosition;

		// 맵에 표시된 '@' 초기화.
		std::vector<std::vector<char>>& map = demoLevel.GetMap();
		for (int y = 0; y < map.size(); ++y)
		{
			for (int x = 0; x < map[y].size(); ++x)
			{
				if (map[y][x] == '@') // 경로 표시된 부분만 초기화.
				{
					map[y][x] = ' '; // 빈 공간으로 변경.
				}
			}
		}

		Game::Get().ToggleLevel("Print Level");
	}
}
