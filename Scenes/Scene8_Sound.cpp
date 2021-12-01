#include "stdafx.h"
#include "Scene8_Sound.h"

Scene8::Scene8()
{
}

Scene8::~Scene8()
{
	Destroy();
}

void Scene8::Init()
{
	string fileName = "_Sounds/war.mp3";
	BGSound = new SoundSystem();
	BGSound->CreateBGSound(fileName);

	EffSound = new SoundSystem();
	EffSound->CreateEffSound("_Sounds/play_fire.wav");
}

void Scene8::Destroy()
{
	SAFE_DELETE(EffSound);
	SAFE_DELETE(BGSound);
}

void Scene8::Update()
{
	if (Keyboard::Get()->Down(VK_01))
		BGSound->Play();
	else if (Keyboard::Get()->Down(VK_02))
		BGSound->Stop();
	else if (Keyboard::Get()->Down(VK_03))
		EffSound->Play();
	else if (Keyboard::Get()->Down(VK_04))
		EffSound->Stop();
	else if (Keyboard::Get()->Down(VK_05))
		EffSound->SetLoop(true);
	else if (Keyboard::Get()->Down(VK_06))
		EffSound->SetLoop(false);

	BGSound->Update();
	EffSound->Update();
}

void Scene8::PreRender()
{
}

void Scene8::Render()
{
	
}

void Scene8::PostRender()
{
	bool temp = true;
	if (ImGui::Begin("Sounds", &temp))
	{
		BGSound->GUI(0);
		EffSound->GUI(1);
	}
	ImGui::End();
}
