#include "Player.h"
#include "Engine/Engine.h"
#include "Algorithm/AStar.h"

Player::Player()
	: DrawableActor("P")
{
	color = Color::Cyan;
	position = Vector2(19, 12);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_RETURN))
	{
		position = Engine::Get().MousePosition();
	}
}
