#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"

// ������ �⺻ ��ü.
class ENGINE_API Actor : public RTTI
{
	// RTTI ����.
	RTTI_DECLARATIONS(Actor, RTTI)

	// Level Ŭ������ friend�� ����.
	// private�� ������ �����ϵ���.
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// ���� ó�� �Լ�.
	virtual void Update(float delatTime);
	virtual void Draw();

	// Getter/Setter.
	virtual void SetPosition(const Vector2& newPosition);
	inline Vector2 Position() const;

	inline bool IsAcive() const { return isActive && !isExpired; }
	inline void SetActive(bool active) { isActive = active; }
	inline void Destroy() { isExpired = true; }

protected:
	// ������ ��ġ.
	Vector2 position;

	// ID(�ؽ�) / �̸� ��.
	// Ȱ��ȭ ���������� ��Ÿ���� ����.
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����.
	bool isExpired;
};