#include "Start.h"
#include "Engine/Engine.h"
#include "Level/DemoLevel.h"
#include "Game/Game.h"

Start::Start(DemoLevel& demoLevel)
	: DrawableActor("S"), demoLevel(demoLevel)
{
	color = Color::Red;
	position = Vector2(5, 3);
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		Vector2 startPosition = Engine::Get().MousePosition();
		if (startPosition.x < 1 || startPosition.x > demoLevel.GetMapWidth() - 2 || startPosition.y < 1 || startPosition.y > demoLevel.GetMapHeight() - 2)
		{
			return;
		}
		if (demoLevel.GetMap()[startPosition.y][startPosition.x] == '#')
		{
			return;
		}
		position = startPosition;

		//Game::Get().ToggleLevel("Print Level");
	}
}
