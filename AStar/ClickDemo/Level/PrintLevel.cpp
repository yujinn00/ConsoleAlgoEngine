#include "PrintLevel.h"
#include "DemoLevel.h"
#include "Engine/Engine.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"

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
}

void PrintLevel::Draw()
{
	Super::Draw();
	
	// ��� Ž���� ������� �ʾҴٸ� ����.
	if (!isPathDrawn)
	{
		DrawPath();
	}

	// Ž���� �Ϸ�Ǿ��ٸ� ��� ���.
	if (isPathDrawn)
	{
		AStar aStar;
		aStar.DisplayGridWithPath(demoLevel.GetMap(), path, pathIndex);
	}
}

void PrintLevel::DrawPath()
{
	if (isPathDrawn) return; // �̹� Ž���Ǿ����� �������� ����.

	if (!demoLevel.GetStart() || !demoLevel.GetEnd())
	{
		return;
	}

	Node* startNode = new Node(demoLevel.GetStart()->GetPosition());
	Node* endNode = new Node(demoLevel.GetEnd()->GetPosition());

	// A* �˰��� ����.
	AStar aStar;
	path = aStar.FindPath(startNode, endNode, demoLevel.GetMap());

	if (!path.empty())
	{
		pathIndex = 0; // ó������ ����.
		isPathDrawn = true; // �� ���� ����.
		elapsedTime = 0.0f; // �ð� �ʱ�ȭ.
	}
}
