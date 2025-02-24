#include "End.h"
#include "Engine/Engine.h"

End::End()
	: DrawableActor("E")
{
	color = Color::Green;
	position = Vector2(34, 21);
}

void End::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		position = Engine::Get().MousePosition();
	}
}
