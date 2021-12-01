#include "stdafx.h"
#include "Scene5_TextureEffect.h"

Scene5::Scene5()
{
}

Scene5::~Scene5()
{
	Destroy();
}

void Scene5::Init()
{
	rect = new Rect(Vector3(200, 200, 0), Vector3(100, 100, 1), 0, Cyan);
	rect2 = new Rect(Vector3(400, 400, 0), Vector3(100, 100, 1), 0);

	RTT = new RenderTexture();
	RTT->Initialize();

	Vector3 size = Vector3(WinMaxWidth, WinMaxHeight, 0);
	texture = new TextureRect(size / 2, size, 0);
	texture->SetSRV(RTT->GetSRV());
	texture->SetShader(L"_Shaders/GrayScale.hlsl");
}

void Scene5::Destroy()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(RTT);
	SAFE_DELETE(rect2);
	SAFE_DELETE(rect);
}

void Scene5::Update()
{
	if (Keyboard::Get()->Press('W'))
		rect->Move(Vector3(0, 300, 0) * Time::Delta());
	else if (Keyboard::Get()->Press('S'))
		rect->Move(Vector3(0, -300, 0) * Time::Delta());
	else if (Keyboard::Get()->Press('A'))
		rect->Move(Vector3(-300, 0, 0) * Time::Delta());
	else if (Keyboard::Get()->Press('D'))
		rect->Move(Vector3(300, 0, 0) * Time::Delta());

	if (Math::RectIntersect(rect, rect2))
		rect2->SetColor(Green);
	else
		rect2->SetColor(Red);

	rect->Update();
	rect2->Update();

	if (Keyboard::Get()->Down(VK_F11))
		RTT->SaveTexture(L"ScreenShot.png");
	texture->Update();
}

void Scene5::PreRender()
{
	Graphics::Get()->SetViewport();
	RTT->RenderToTexture();
	{
		rect->Render();
		rect2->Render();
	}
	Graphics::Get()->SetBackBufferToRTV();
}

void Scene5::Render()
{
	texture->Render();
}
