#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player();

	virtual void Update(float deltaTime) override;

	// 위치 정보 반환
	Vector2 GetPosition() const { return position; }

private:
	// 위치 정보 저장
	Vector2 position;
};
