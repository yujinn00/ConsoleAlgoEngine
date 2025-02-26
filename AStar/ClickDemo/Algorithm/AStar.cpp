#include <iostream>

#include "AStar.h"
#include "Node.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"

AStar::AStar()
	: startNode(nullptr), goalNode(nullptr)
{
}

AStar::~AStar()
{
	// �޸� ����.
	for (Node* node : openList)
	{
		SafeDelete(node);
	}
	openList.clear();

	for (Node* node : closedList)
	{
		SafeDelete(node);
	}
	closedList.clear();
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<char>>& grid)
{
	this->startNode = startNode;
	this->goalNode = goalNode;

	for (Node* node : openList)
	{
		SafeDelete(node);
	}
	openList.clear();

	for (Node* node : closedList)
	{
		SafeDelete(node);
	}
	closedList.clear();

	// ���� ��带 ���� ����Ʈ(OpenList)�� �߰�.
	openList.emplace_back(startNode);

	// �����¿� �� �밢�� �̵� ����� ���.
	std::vector<Direction> directions =
	{
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// �밢�� �̵�.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f }
	};

	// �̿� ��� Ž�� (���� ����Ʈ�� ��� ���� ���� ���� �ݺ�).
	while (!openList.empty())
	{
		// ���� ���� ����Ʈ���� fCost�� ���� ���� ��� �˻�.
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		// fCost�� ���� ���� ��带 ���� ���� ����.
		Node* currentNode = lowestNode;

		// ���� ��尡 ��ǥ ������� Ȯ�� �� ������ ����.
		if (IsDestination(currentNode))
		{
			return ConstructPath(currentNode);
		}

		// �湮 ó���� ���� ���� ��带 ���� ����Ʈ���� ����.
		for (int ix = 0; ix < static_cast<int>(openList.size()); ++ix)
		{
			if (*openList[ix] == *currentNode)
			{
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		// �湮 ó���� ���� ���� ��带 ���� ����Ʈ�� �߰�.
		// �̹� ���� ��忡 �ִ� ������� Ȯ�� �Ŀ� ������ �߰�.
		bool isNodeInList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		if (isNodeInList)
		{
			continue;
		}

		closedList.emplace_back(currentNode);

		// �̿� ��� Ž��. (�ϻ���� ���ʷ� Ž��).
		for (const Direction& direction : directions)
		{
			// ������ �̵��� ��ġ ����.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			// �׸��� ���̸� ����.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// �̵��� ��ġ�� ��ֹ��� ��쿡�� ����.
			if (grid[newY][newX] == '#')
			{
				continue;
			}

			// �̹� �湮�� ����� ��� ����.
			if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
			{
				continue;
			}

			// �湮�� ���� �̿� ��� ����.
			// �湮�� ����� gCost, hCost, fCost ���.
			Node* neighborNode = new Node(Vector2(newX, newY), currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			// �̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��.
			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			// �̿� ��尡 ���� ����Ʈ�� ���� ���, �湮�� ���� ���� ����Ʈ�� �߰�.
			// �̿� ��尡 ���� ����Ʈ�� �ִٸ�, gCost�� fCost�� ���� �� ���� ��쿡 ���� ����Ʈ�� �߰�.
			if (openListNode == nullptr
				|| neighborNode->gCost < openListNode->gCost
				|| neighborNode->fCost < openListNode->fCost)
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);
			}
		}
	}

	return {};
}

void AStar::DisplayGridWithPath(std::vector<std::vector<char>>& grid, const std::vector<Node*>& path, int pathIndex)
{
	// ���� ó��.
	if (path.size() <= 2)
	{
		return;
	}

	// ù ��°�� ������ ��� ��ġ ��������.
	int startY = path.front()->position.y;
	int startX = path.front()->position.x;
	int endY = path.back()->position.y;
	int endX = path.back()->position.x;

	// ���� pathIndex������ ��θ� '@'�� ǥ�� (ù ��°�� ������ ����).
	for (int i = 1; i < pathIndex && i < path.size(); ++i)
	{
		// ���� ó��.
		if (!path[i])
		{
			continue;
		}

		int y = path[i]->position.y;
		int x = path[i]->position.x;

		// ��δ� '@'�� ǥ�� (���� üũ).
		if (y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size())
		{
			grid[y][x] = '@';
		}
	}

	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			if (y == startY && x == startX)
				Engine::Get().Draw(Vector2(x, y), "S", Color::Green);
			else if (y == endY && x == endX)
				Engine::Get().Draw(Vector2(x, y), "E", Color::Red);
			else if (grid[y][x] == '#')
				Engine::Get().Draw(Vector2(x, y), "#", Color::White);
			else if (grid[y][x] == '@')
				Engine::Get().Draw(Vector2(x, y), "@", Color::Yellow);
			else
				Engine::Get().Draw(Vector2(x, y), " ", Color::White);
		}
	}
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	// ��ǥ ��� ����, �θ� ��带 ���� �������ϸ鼭 ��� ��� ����.
	std::vector<Node*> path;
	Node* currentNode = goalNode;

	while (currentNode != nullptr)
	{
		path.emplace_back(new Node(*currentNode));
		currentNode = currentNode->parent;
	}

	std::reverse(path.begin(), path.end());
	return path;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
	// ���� ����� ��ġ���� ��ǥ ��ġ������ �Ÿ��� �޸���ƽ ������ ���.
	Vector2 diff = *currentNode - *goalNode;
	return static_cast<float>(std::sqrt(std::pow(diff.x, 2) + std::pow(diff.y, 2)));
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<char>>& grid)
{
	// x, y ������ ����� false ��ȯ.
	if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
	{
		return false;
	}

	// ����� �ʾ����� true ��ȯ.
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// ���� ����Ʈ�� ���� ����Ʈ�� �̹� �ش� ��ġ�� ��尡 ������ �湮�� ������ �Ǵ�.
	for (int ix = 0; ix < static_cast<int>(openList.size()); ++ix)
	{
		Node* node = openList[ix];
		if ((node->position.x == x && node->position.y == y))
		{
			// ��ġ�� ����, ����� �� ũ�� �湮�� ������ ���� ������ �湮�ߴٰ� �Ǵ�.
			if (gCost >= node->gCost)
			{
				return true;
			}

			// ��ġ�� ������, ����� ���� ���, �湮�� �ʿ䰡 �����Ƿ�, ������ ��� ����.
			else
			{
				openList.erase(openList.begin() + ix);
				SafeDelete(node);
			}
		}
	}

	for (int ix = 0; ix < static_cast<int>(closedList.size()); ++ix)
	{
		Node* node = closedList[ix];
		if ((node->position.x == x && node->position.y == y))
		{
			// ��ġ�� ����, ����� �� ũ�� �湮�� ������ ���� ������ �湮�ߴٰ� �Ǵ�.
			if (gCost >= node->gCost)
			{
				return true;
			}

			// ��ġ�� ������, ����� ���� ���, �湮�� �ʿ䰡 �����Ƿ�, ������ ��� ����.
			else
			{
				closedList.erase(closedList.begin() + ix);
				SafeDelete(node);
			}
		}
	}

	// ����Ʈ�� ������ �湮���� ���� ������ �Ǵ�.
	return false;
}

bool AStar::IsDestination(Node* node)
{
	// ����� ��ġ�� ���� ������ ��.
	return *node == *goalNode;
}
