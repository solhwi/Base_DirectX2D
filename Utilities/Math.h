#pragma once

class Object;

class Math
{
public:
	static bool RectIntersect(Object* rect1, Object* rect2);

	static bool RectOBBIntersect(Object* rect, Object* rect2);

	static Vector2 absVec2(Vector2 val);
	static Vector3 absVec3(Vector3 val);

	static float GetDistance(Vector3 vec1, Vector3 vec2);
	static float Dot(Vector3 vec1, Vector3 vec2);
};