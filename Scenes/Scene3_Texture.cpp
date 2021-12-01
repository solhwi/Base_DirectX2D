#include "stdafx.h"
#include "Scene3_Texture.h"

Scene3::Scene3()
{
}

Scene3::~Scene3()
{
	Destroy();
}

void Scene3::Init()
{
	Vector3 size = Vector3(WinMaxWidth / 3, WinMaxHeight / 3, 0);
	rect = new Rect(size / 2, size, 0);
	texture = new TextureRect(size / 2, size, 0, L"_Textures/bk.bmp");

	RTT = new RenderTexture();
	RTT->Initialize();
}

void Scene3::Destroy()
{
	SAFE_DELETE(RTT);
	SAFE_DELETE(rect);
	SAFE_DELETE(texture);
}

void Scene3::Update()
{
	if (Keyboard::Get()->Down(VK_F11))
		RTT->SaveTexture(L"ScreenShot.png");
	texture->Update();
	rect->Update();
}

void Scene3::PreRender()
{
	Graphics::Get()->SetViewport();
	RTT->RenderToTexture();
	{
		//texture->Render();
		rect->Render();
	}
	Graphics::Get()->SetBackBufferToRTV();
}

void Scene3::Render()
{
	texture->Render();
}
