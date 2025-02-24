#pragma once

#include <vector>

// A* ��ã�� ����� ó���ϴ� Ŭ����.
class Node;
class AStar
{
private:

	// ���� ó���� ���� ����ü.
	struct Direction
	{
		// ��ġ.
		int x;
		int y;

		// �̵� ���
		float cost;
	};

public:
	AStar();
	~AStar();

	// ��� �˻� �Լ�.
	std::vector<Node*> FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid);

	// �׸��� ��� �Լ�.
	void DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path);

private:
	// Ž���� ��ģ �� ���� ��θ� ��ȯ�ϴ� �Լ�.
	// ��ǥ ��忡�� �θ� ��带 ������ ���۳����� �������ϸ� ��θ� ���� �� �ִ�.
	std::vector<Node*> ConstructPath(Node* goalNode);

	// hCost ��� �Լ�.
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	// Ž���Ϸ��� ��ġ�� �׸��� ���� �ȿ� �ִ��� Ȯ���ϴ� �Լ�.
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	// �湮�Ϸ��� ��ġ�� �̹� �湮�ߴ� ������� Ȯ���ϴ� �Լ�.
	bool HasVisited(int x, int y, float gCost);

	// Ž���Ϸ��� ��尡 ��ǥ ������� Ȯ���ϴ� �Լ�.
	bool IsDestination(Node* node);

private:

	// ���� ����Ʈ.
	std::vector<Node*> openList;

	// ���� ����Ʈ.
	std::vector<Node*> closedList;

	// ���� ���.
	Node* startNode;

	// ��ǥ ���.
	Node* goalNode;
};