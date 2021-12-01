#include "stdafx.h"
#include "Math.h"

bool Math::RectIntersect(Object * rect, Object * rect2)
{
	RectEdges e1 = rect->GetTransformCoord();
	RectEdges e2 = rect2->GetTransformCoord();

	if (e1.LT.x <= e2.RB.x
		&& e1.RB.x >= e2.LT.x
		&& e1.LT.y >= e2.RB.y
		&& e1.RB.y <= e2.LT.y)
		return true;
	else
		return false;
}

bool Math::RectOBBIntersect(Object * rect1, Object * rect2)
{
	Vector3 dist = rect1->GetPosition() - rect2->GetPosition();

	Vector3 r1Up = rect1->Up() * rect1->GetScale().y * 0.5f;
	Vector3 r1Right = rect1->Right() * rect1->GetScale().x * 0.5f;

	Vector3 r2Up = rect2->Up() * rect2->GetScale().y * 0.5f;
	Vector3 r2Right = rect2->Right() * rect2->GetScale().x * 0.5f;

	float c = fabs(Dot(dist, rect1->Right()));
	float a = fabs(Dot(r2Up, rect1->Right())) + fabs(Dot(r2Right, rect1->Right()));
	float b = rect1->GetScale().x * 0.5f;

	if (c > a + b) return false;

	c = fabs(Dot(dist, rect1->Up()));
	a = fabs(Dot(r2Up, rect1->Up())) + fabs(Dot(r2Right, rect1->Up()));
	b = rect1->GetScale().y * 0.5f;

	if (c > a + b) return false;

	c = fabs(Dot(dist, rect2->Right()));
	a = fabs(Dot(r1Up, rect2->Right())) + fabs(Dot(r1Right, rect2->Right()));
	b = rect1->GetScale().x * 0.5f;

	if (c > a + b) return false;

	c = fabs(Dot(dist, rect2->Up()));
	a = fabs(Dot(r1Up, rect2->Up())) + fabs(Dot(r1Right, rect2->Up()));
	b = rect1->GetScale().y * 0.5f;

	if (c > a + b) return false;

	return true;

}

Vector2 Math::absVec2(Vector2 val)
{
	return Vector2(abs(val.x), abs(val.y));
}

Vector3 Math::absVec3(Vector3 val)
{
	return Vector3(abs(val.x), abs(val.y), abs(val.z));
}

float Math::GetDistance(Vector3 vec1, Vector3 vec2)
{
	return sqrtf(powf(vec1.x - vec2.x, 2) + powf(vec1.y - vec2.y, 2));
}

float Math::Dot(Vector3 vec1, Vector3 vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
