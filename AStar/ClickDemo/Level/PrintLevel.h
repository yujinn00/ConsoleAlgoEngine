#pragma once

#include "Level/Level.h"
#include "Algorithm/Node.h"

class DemoLevel;
class PrintLevel : public Level
{
	// RTTI 정의.
	RTTI_DECLARATIONS(PrintLevel, Level)

public:
	// 생성자로 DemoLevel 참조 전달.
	PrintLevel(DemoLevel& demoLevel);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// 저장한 경로를 출력.
	void DrawPath();

private:
	DemoLevel& demoLevel;

	// A* 경로 저장.
	std::vector<Node*> path;

	// 현재 출력할 경로 인덱스.
	int pathIndex = 0;

	// 경로 탐색 완료 여부.
	bool isPathDrawn = false;

	// 경과 시간 누적 변수.
	float elapsedTime = 0.0f;

	// 0.2초마다 한 칸씩 출력.
	float drawInterval = 0.2f;
};
