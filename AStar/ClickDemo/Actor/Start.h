#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class Start : public DrawableActor
{
	RTTI_DECLARATIONS(Start, DrawableActor)

public:
	Start();

	virtual void Update(float deltaTime) override;

	// ��ġ ���� ��ȯ.
	Vector2 GetPosition() const { return position; }

private:
	// ��ġ ���� ����.
	Vector2 position;
};
