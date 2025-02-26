#include "PrintLevel.h"
#include "DemoLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

PrintLevel::PrintLevel(DemoLevel& demoLevel)
	: demoLevel(demoLevel)
{
}

void PrintLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if (Engine::Get().GetKeyDown(VK_RETURN))
	{
		ResetPath();
		Game::Get().ToggleLevel("Demo Level");
	}

	// 경로가 탐색되었고, 아직 끝까지 도달하지 않았다면 실행.
	if (isPathDrawn && pathIndex < path.size())
	{
		elapsedTime += deltaTime;

		// 일정 시간이 지나면 pathIndex 증가.
		if (elapsedTime >= drawInterval)
		{
			elapsedTime = 0.0f; // 시간 초기화.
			pathIndex++; // 한 칸씩 진행.
		}
	}
}

void PrintLevel::Draw()
{
	Super::Draw();

	// 경로 탐색이 수행되지 않았다면 실행.
	if (!isPathDrawn)
	{
		SavePath();
	}

	// 탐색이 완료되었다면 경로 출력.
	if (isPathDrawn)
	{
		aStar.DisplayGridWithPath(demoLevel.GetMap(), path, pathIndex);
	}
}

void PrintLevel::SavePath()
{
	// 이미 탐색되었으면 실행하지 않음.
	if (isPathDrawn) return;

	if (!demoLevel.GetStart() || !demoLevel.GetEnd())
	{
		std::cout << "스타트나 엔드가 없습니다.\n";
		return;
	}

	Node* startNode = new Node(demoLevel.GetStart()->GetPosition());
	Node* endNode = new Node(demoLevel.GetEnd()->GetPosition());

	// A* 알고리즘 실행.
	path = aStar.FindPath(startNode, endNode, demoLevel.GetMap());

	if (!path.empty())
	{
		pathIndex = 0; // 처음부터 시작.
		isPathDrawn = true; // 한 번만 실행.
		elapsedTime = 0.0f; // 시간 초기화.
	}
}

void PrintLevel::ResetPath()
{
	// 경로 데이터 초기화.
	path.clear();
	pathIndex = 0;
	isPathDrawn = false;

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
}
