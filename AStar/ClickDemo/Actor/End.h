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

	// ��ġ ���� ��ȯ.
	Vector2 GetPosition() const { return position; }

private:
	DemoLevel& demoLevel;

	// ��ġ ���� ����.
	Vector2 position;
};
