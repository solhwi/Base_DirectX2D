#include "stdafx.h"
#include "Scene7_Blur.h"

Scene7::Scene7()
{
}

Scene7::~Scene7()
{
	Destroy();
}

void Scene7::Init()
{
	Vector3 size = Vector3(WinMaxWidth, WinMaxHeight, 0);
	texture = new TextureRect(size / 2, size, 0, L"_Textures/bk.bmp");
	texture->SetShader(L"_Shaders/Blur.hlsl");
}

void Scene7::Destroy()
{
	SAFE_DELETE(texture);
}

void Scene7::Update()
{
	if (Keyboard::Get()->Press('W'))
		texture->MoveLocalRect(Vector4(0, -10, 0, -10));
	else if (Keyboard::Get()->Press('S'))
		texture->MoveLocalRect(Vector4(0, 10, 0, 10));
	else if (Keyboard::Get()->Press('A'))
		texture->MoveLocalRect(Vector4(-10, 0, -10, 0));
	else if (Keyboard::Get()->Press('D'))
		texture->MoveLocalRect(Vector4(10, 0, 10, 0));

	texture->Update();
}

void Scene7::Render()
{
	texture->Render();
}
