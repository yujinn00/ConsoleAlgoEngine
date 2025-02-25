#pragma once

#include "Level/Level.h"
#include "Algorithm/Node.h"

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
	void DrawPath();

private:
	DemoLevel& demoLevel;

	// A* ��� ����.
	std::vector<Node*> path;

	// ���� ����� ��� �ε���.
	int pathIndex = 0;

	// ��� Ž�� �Ϸ� ����.
	bool isPathDrawn = false;

	// ��� �ð� ���� ����.
	float elapsedTime = 0.0f;

	// 0.2�ʸ��� �� ĭ�� ���.
	float drawInterval = 0.2f;
};
