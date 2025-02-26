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

	// ��ΰ� Ž���Ǿ���, ���� ������ �������� �ʾҴٸ� ����.
	if (isPathDrawn && pathIndex < path.size())
	{
		elapsedTime += deltaTime;

		// ���� �ð��� ������ pathIndex ����.
		if (elapsedTime >= drawInterval)
		{
			elapsedTime = 0.0f; // �ð� �ʱ�ȭ.
			pathIndex++; // �� ĭ�� ����.
		}
	}

	// ��� ����� ������ �ڵ����� DemoLevel�� ��ȯ.
	if (isPathDrawn && pathIndex >= path.size())
	{
		ResetPath(); // ���� ��� �ʱ�ȭ.
		Game::Get().ToggleLevel("Demo Level"); // �ڵ����� DemoLevel�� ��ȯ.
	}
}

void PrintLevel::Draw()
{
	Super::Draw();

	// ��� Ž���� ������� �ʾҴٸ� ����.
	if (!isPathDrawn)
	{
		SavePath();
	}

	// Ž���� �Ϸ�Ǿ��ٸ� ��� ���.
	if (isPathDrawn)
	{
		aStar.DisplayGridWithPath(demoLevel.GetMap(), path, pathIndex);
	}
}

void PrintLevel::SavePath()
{
	// �̹� Ž���Ǿ����� �������� ����.
	if (isPathDrawn) return;

	if (!demoLevel.GetStart() || !demoLevel.GetEnd())
	{
		return;
	}

	Node* startNode = new Node(demoLevel.GetStart()->GetPosition());
	Node* endNode = new Node(demoLevel.GetEnd()->GetPosition());

	// A* �˰��� ����.
	path = aStar.FindPath(startNode, endNode, demoLevel.GetMap());

	if (!path.empty())
	{
		pathIndex = 0; // ó������ ����.
		isPathDrawn = true; // �� ���� ����.
		elapsedTime = 0.0f; // �ð� �ʱ�ȭ.
	}
}

void PrintLevel::ResetPath()
{
	// ��� ������ �ʱ�ȭ.
	path.clear();
	pathIndex = 0;
	isPathDrawn = false;
}
