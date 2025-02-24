#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player();

	virtual void Update(float deltaTime) override;

	// ��ġ ���� ��ȯ
	Vector2 GetPosition() const { return position; }

private:
	// ��ġ ���� ����
	Vector2 position;
};
