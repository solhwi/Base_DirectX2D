#include "stdafx.h"
#include "Scene12_TileMap.h"

Scene12::Scene12()
{
}

Scene12::~Scene12()
{
	Destroy();
}

void Scene12::Init()
{
	tileMap = new TileMap(Vector3(0, 0, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0, 40);
}

void Scene12::Destroy()
{
	SAFE_DELETE(tileMap);
}

void Scene12::Update()
{
	tileMap->Update();
}

void Scene12::PreRender()
{
}

void Scene12::Render()
{
	tileMap->Render();
}

void Scene12::PostRender()
{
	tileMap->GUI();
}
