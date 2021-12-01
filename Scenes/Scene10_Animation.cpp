#include "stdafx.h"
#include "Scene10_Animation.h"

Scene10::Scene10()
{
}

Scene10::~Scene10()
{
}

void Scene10::Init()
{
	background = new TextureRect(Vector3(400 * 3.0f, 400 * 3.0f, 0), Vector3(800 * 3.0f, 800 * 3.0f, 1), 0);
	mapTex = new Texture2D(L"_Textures/Map.png");
	background->SetSRV(mapTex->GetSRV());
	Camera::Get()->SetEdges(Vector2(0, 0), Vector2(800 * 3.0f, 800 * 3.0f));
	rockman = new Rockman(Vector3(300, 300, 0), Vector3(100, 100, 1), 0, L"_Textures/rockman.bmp");
}

void Scene10::Destroy()
{
	SAFE_DELETE(rockman);
}

void Scene10::Update()
{
	background->Update();

	if (Keyboard::Get()->Press('W'))
		rockman->Move(Vector3(0, 10, 0));
	else if (Keyboard::Get()->Press('S'))
		rockman->Move(Vector3(0, -10, 0));
	else if (Keyboard::Get()->Press('A'))
		rockman->Move(Vector3(-10, 0, 0));
	else if (Keyboard::Get()->Press('D'))
		rockman->Move(Vector3(10, 0, 0));


	rockman->Update();
	Camera::Get()->Move(rockman->GetPosition() - Vector3(WinMaxWidth / 3, WinMaxHeight / 3, 0));
}

void Scene10::PreRender()
{
}

void Scene10::Render()
{
	background->Render();
	rockman->Render();
}

void Scene10::PostRender()
{
}
