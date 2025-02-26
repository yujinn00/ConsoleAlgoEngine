#include "End.h"
#include "Engine/Engine.h"
#include "Level/DemoLevel.h"
#include "Game/Game.h"

End::End(DemoLevel& demoLevel)
	: DrawableActor("E"), demoLevel(demoLevel)
{
	color = Color::Green;
	position = Vector2(34, 21);
}

void End::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		Vector2 endPosition = Engine::Get().MousePosition();
		if (endPosition.x < 1 || endPosition.x > demoLevel.GetMapWidth() - 2 || endPosition.y < 1 || endPosition.y > demoLevel.GetMapHeight() - 2)
		{
			return;
		}
		if (demoLevel.GetMap()[endPosition.y][endPosition.x] == '#')
		{
			return;
		}
		position = endPosition;

		//Game::Get().ToggleLevel("Print Level");
	}
}
