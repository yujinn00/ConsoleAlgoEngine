#pragma once

#include "Level/Level.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"

class DemoLevel;
class PrintLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(PrintLevel, Level)

public:
	// �����ڷ� DemoLevel ���� ����.
	PrintLevel(DemoLevel& demoLevel);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// ������ ��θ� ���.
	void SavePath();

	// ����� ��θ� �ʱ�ȭ.
	void ResetPath();

private:
	DemoLevel& demoLevel;

	// Astar ��ü ����.
	AStar aStar;

	// A* ��� ����.
	std::vector<Node*> path;

	// ���� ����� ��� �ε���.
	int pathIndex = 0;

	// ��� Ž�� �Ϸ� ����.
	bool isPathDrawn = false;

	// ��� �ð� ���� ����.
	float elapsedTime = 0.0f;

	// 0.1�ʸ��� �� ĭ�� ���.
	float drawInterval = 0.1f;
};
