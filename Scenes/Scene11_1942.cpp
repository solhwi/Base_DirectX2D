#include "stdafx.h"
#include "Scene11_1942.h"

Scene11::Scene11()
{
}

Scene11::~Scene11()
{
	Destroy();
}

void Scene11::Init()
{
	player = new Airplane(Vector3(300, 300, 0), Vector3(100, 100, 1), 0, L"_Textures/1945/AV-8.png");

	for (int i = 0; i < 10; i++)
	{
		cannons.push_back(new Cannon(Vector3(200 * i, 500 + i * 2, 0), Vector3(100, 100, 1), 0, L"_Textures/Tree.png"));
	}
}

void Scene11::Destroy()
{
	SAFE_DELETE(player);

	/*for (auto cannon : cannons)
	{
		SAFE_DELETE(cannon);
	}*/
}

void Scene11::Update()
{
	if (Keyboard::Get()->Press('W'))
		player->Move(Vector3(0, 10, 0));
	else if (Keyboard::Get()->Press('S'))
		player->Move(Vector3(0, -10, 0));
	else if (Keyboard::Get()->Press('A'))
		player->Move(Vector3(-10, 0, 0));
	else if (Keyboard::Get()->Press('D'))
		player->Move(Vector3(10, 0, 0));

	if(Keyboard::Get()->Down('J')) // ÀÏ¹Ý °ø°Ý
	{
		player->Attack();
	}
	else if (Keyboard::Get()->Down('K')) // ÆøÅº
	{
		player->Bomb();
	}

	for (int i = 0; i < cannons.size(); i++) // ºÎ½¤Áø Ä³³í Ã³¸®
	{
		player->Hit(cannons[i]);

		if (cannons[i]->isDestroyed)
		{
			SAFE_DELETE(cannons[i]);
			cannons.erase(cannons.begin() + i--);
		}
	}

	player->Update();

	for (const auto& cannon : cannons)
	{
		cannon->Update();
	}
}

void Scene11::PreRender()
{
}

void Scene11::Render()
{
	player->Render();

	for (const auto& cannon : cannons)
	{
		cannon->Render();
	}
}

void Scene11::PostRender()
{
}
