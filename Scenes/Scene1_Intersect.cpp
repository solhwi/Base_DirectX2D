#include "stdafx.h"
#include "Scene1_Intersect.h"

Scene1::Scene1()
{
	Init();
}

Scene1::~Scene1()
{
	Destroy();
}

void Scene1::Init()
{
	rect = new Rect(Vector3(200, 200, 0), Vector3(100, 100, 1), 50, Cyan);
	rect2 = new Rect(Vector3(400, 400, 0), Vector3(100, 100, 1), 0);
}

void Scene1::Destroy()
{
	SAFE_DELETE(rect2);
	SAFE_DELETE(rect);
}

void Scene1::Update()
{
	if (Keyboard::Get()->Press('W'))
		rect->Move(Vector3(0, 300, 0) * Time::Delta());
	else if (Keyboard::Get()->Press('S'))
		rect->Move(Vector3(0, -300, 0) * Time::Delta());
	else if (Keyboard::Get()->Press('A'))
		rect->Move(Vector3(-300, 0, 0) * Time::Delta());
	else if (Keyboard::Get()->Press('D'))
		rect->Move(Vector3(300, 0, 0) * Time::Delta());

	if (Math::RectOBBIntersect(rect, rect2))
		rect2->SetColor(Green);
	else
		rect2->SetColor(Red);

	rect->Update();
	rect2->Update();
}

void Scene1::Render()
{
	rect->Render();
	rect2->Render();
}