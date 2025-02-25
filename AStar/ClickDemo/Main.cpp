#include "Game/Game.h"

int main()
{
	Game game;
	game.LoadLevel(game.LoadDemoLevel());
	game.Run();
}
