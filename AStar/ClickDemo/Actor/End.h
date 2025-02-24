#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class End : public DrawableActor
{
	RTTI_DECLARATIONS(End, DrawableActor)

public:
	End();

	virtual void Update(float deltaTime) override;

	// ��ġ ���� ��ȯ.
	Vector2 GetPosition() const { return position; }

private:
	// ��ġ ���� ����.
	Vector2 position;
};
