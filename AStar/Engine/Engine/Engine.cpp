#include "PreCompiledHeader.h"

#include "Engine.h"
#include <Windows.h>
#include <iostream>

#include "Level/Level.h"
#include "Actor/Actor.h"

#include <time.h>

#include "Render/ScreenBuffer.h"

// �ܼ� â �޽��� �ݹ� �Լ�.
BOOL WINAPI MessageProcessor(DWORD message)
{
	switch (message)
	{
	case CTRL_CLOSE_EVENT:
		Engine::Get().QuitGame();
		return true;

	default:
		return false;
	}
}

// ����ƽ ���� �ʱ�ȭ.
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(nullptr), screenSize(40, 25)
{
	// ���� �õ� ����.
	srand((unsigned int)time(nullptr));

	// �̱��� ��ü ����.
	instance = this;

	// �⺻ Ÿ�� ������ �ӵ� ����.
	SetTargetFrameRate(60.0f);

	// ȭ�� ���� �ʱ�ȭ.
	// 1. ���� ũ�� �Ҵ�.
	imageBuffer = new CHAR_INFO[(screenSize.x + 1) * screenSize.y + 1];

	// ���� �ʱ�ȭ.
	ClearImageBuffer();

	// �� ���� ���� ���� (���۸� ������ ����ϱ� ����-���� ���۸�).
	COORD size = { (short)screenSize.x, (short)screenSize.y };
	//renderTargets[0] = new ScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE), size);
	renderTargets[0] = new ScreenBuffer(size);
	renderTargets[1] = new ScreenBuffer(size);

	// ���� ����.
	Present();

	// �ܼ� â �̺�Ʈ �ݹ� �Լ� ���.
	SetConsoleCtrlHandler(MessageProcessor, true);

	// ���콺/������ �̺�Ʈ Ȱ��ȭ.
	HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	int flag = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(inputHandle, flag);

	// std::cin/std::cout ���� ����.
	std::ios::sync_with_stdio(false);
}

Engine::~Engine()
{
	// ���� ���� �޸� ����.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}

	// Ŭ���� ���� ����.
	delete[] imageBuffer;

	// ȭ�� ���� ����.
	delete renderTargets[0];
	delete renderTargets[1];
}

void Engine::Run()
{
	// �ý��� �ð� -> ���ػ� ī����. (10000000).
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// ���� �ð� �� ���� �ð��� ���� ����.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;

	// Game-Loop.
	while (true)
	{
		// ���� ����.
		if (quit)
		{
			break;
		}

		// ���� ������ �ð� ����.
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// ������ �ð� ���.
		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		// ������ Ȯ��.
		if (deltaTime >= targetOneFrameTime)
		{
			// �Է� ó�� (���� Ű/���콺 �Է� ���� Ȯ��).
			ProcessInput();

			// ������Ʈ ������ ���¿����� ������ ������Ʈ ó��.
			//if (shouldUpdate)
			//{
			//	Update(deltaTime);
			//	Draw();
			//}

			Update(deltaTime);
			Draw();

			// Ű ���� ����.
			SavePreviouseKeyStates();

			// ���� ������ �ð� ����.
			previousTime = currentTime;

			// ���� ���� (�߰� �� ���� ��û�� ���͵� ����).
			if (mainLevel)
			{
				mainLevel->ProcessAddedAndDestroyedActor();
			}

			// ������ Ȱ��ȭ.
			//shouldUpdate = true;
		}
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// ���� ������ �ִٸ� ���� �� ��ü.

	// ���� ���� ����.
	mainLevel = newLevel;
}

void Engine::AddActor(Actor* newActor)
{
	// ���� ó��.
	if (mainLevel == nullptr)
	{
		return;
	}

	// ������ ���� �߰�.
	//shouldUpdate = false;
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// ���� ó��.
	if (mainLevel == nullptr)
	{
		return;
	}

	// ������ ���� �߰�.
	//shouldUpdate = false;
	targetActor->Destroy();
}

void Engine::SetCursorType(CursorType cursorType)
{
	GetRenderer()->SetCursorType(cursorType);
}

void Engine::Draw(const Vector2& position, const char* image, Color color)
{
	for (int ix = 0; ix < (int)strlen(image); ++ix)
	{
		int index = (position.y * (screenSize.x)) + position.x + ix;
		imageBuffer[index].Char.AsciiChar = image[ix];
		imageBuffer[index].Attributes = (unsigned long)color;
	}
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

Vector2 Engine::MousePosition() const
{
	return mousePosition;
}

void Engine::QuitGame()
{
	// ���� �÷��� ����.
	quit = true;
}

Engine& Engine::Get()
{
	// �̱��� ��ü ��ȯ.
	return *instance;
}

void Engine::ProcessInput()
{
	static HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);

	INPUT_RECORD record;
	DWORD events;
	if (PeekConsoleInput(inputHandle, &record, 1, &events) && events > 0)
	{
		if (ReadConsoleInput(inputHandle, &record, 1, &events))
		{
			switch (record.EventType)
			{
			case KEY_EVENT:
			{
				// Ű ���� ���� ������Ʈ.
				if (record.Event.KeyEvent.bKeyDown)
				{
					keyState[record.Event.KeyEvent.wVirtualKeyCode].isKeyDown = true;
				}
				// Ű ���� ���� ���� ������Ʈ.
				else
				{
					keyState[record.Event.KeyEvent.wVirtualKeyCode].isKeyDown = false;
				}
			}
			break;

			case MOUSE_EVENT:
			{
				// ���콺 Ŀ�� ��ġ ������Ʈ.
				mousePosition.x = record.Event.MouseEvent.dwMousePosition.X;
				mousePosition.y = record.Event.MouseEvent.dwMousePosition.Y;

				// ���콺 ���� ��ư Ŭ�� ���� ������Ʈ.
				keyState[VK_LBUTTON].isKeyDown
					= (record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0;

				// ���콺 ������ ��ư Ŭ�� ���� ������Ʈ.
				keyState[VK_RBUTTON].isKeyDown
					= (record.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) != 0;
			}
			break;

			//		//case WINDOW_BUFFER_SIZE_EVENT:
			//{
			//	char buffer[100];
			//	sprintf_s(buffer, 100, "(%d,%d)", 
			//		record.Event.WindowBufferSizeEvent.dwSize.X, record.Event.WindowBufferSizeEvent.dwSize.Y
			//	);

			//	MessageBoxA(nullptr, buffer, "Test", MB_OK);
			//} break;
			}
		}
	}

	//// Ű �Է� �׽�Ʈ.
	//for (int ix = 0; ix < 255; ++ix)
	//{
	//	keyState[ix].isKeyDown = (GetAsyncKeyState(ix) & 0x8000) ? true : false;
	//}
}

void Engine::Update(float deltaTime)
{
	// ���� ������Ʈ.
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}
}

void Engine::Clear()
{
	ClearImageBuffer();
	//GetRenderer()->Clear();
}

void Engine::Draw()
{
	// ȭ�� �����.
	Clear();

	//char buffer[256];
	//snprintf(buffer, 256, "mouse position: (%d,%d)\n", mousePosition.x, mousePosition.y);
	//Draw(Vector2(15, 1), buffer);

	//const char* state = (keyState['a'].isKeyDown) ? "True" : "False";
	//snprintf(buffer, 256, "keyState: %s", state);
	//Draw(Vector2(15, 2), buffer);

	// ���� �׸���.
	if (mainLevel != nullptr)
	{
		mainLevel->Draw();
	}

	// ����ۿ� ������ ����.
	GetRenderer()->Draw(imageBuffer);

	// ����Ʈ<->�� ���� ��ȯ.
	Present();
}

void Engine::Present()
{
	// Swap Buffer.
	SetConsoleActiveScreenBuffer(GetRenderer()->buffer);
	currentRenderTargetIndex = 1 - currentRenderTargetIndex;
}

void Engine::SavePreviouseKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].wasKeyDown = keyState[ix].isKeyDown;
	}
}

void Engine::ClearImageBuffer()
{
	// ���� �����.
	for (int y = 0; y < screenSize.y; ++y)
	{
		// ���� �����.
		for (int x = 0; x < screenSize.x + 1; ++x)
		{
			auto& buffer = imageBuffer[(y * (screenSize.x + 1)) + x];
			buffer.Char.AsciiChar = ' ';
			buffer.Attributes = 0;
		}

		// �� �� ���� ���� ���� �߰�.
		auto& buffer = imageBuffer[(y * (screenSize.x + 1)) + screenSize.x];
		buffer.Char.AsciiChar = '\n';
		buffer.Attributes = 0;
	}

	// �������� �� ���� �߰�.
	auto& buffer = imageBuffer[(screenSize.x + 1) * screenSize.y];
	buffer.Char.AsciiChar = '\0';
	buffer.Attributes = 0;
}