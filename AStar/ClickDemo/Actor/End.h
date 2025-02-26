#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class DemoLevel;
class End : public DrawableActor
{
	RTTI_DECLARATIONS(End, DrawableActor)

public:
	End(DemoLevel& demoLevel);

	virtual void Update(float deltaTime) override;

	// 위치 정보 반환.
	Vector2 GetPosition() const { return position; }

private:
	DemoLevel& demoLevel;

	// 위치 정보 저장.
	Vector2 position;
};
