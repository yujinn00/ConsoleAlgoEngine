#include "Start.h"
#include "Engine/Engine.h"

Start::Start()
	: DrawableActor("S")
{
	color = Color::Red;
	position = Vector2(5, 3);
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		position = Engine::Get().MousePosition();
	}
}
