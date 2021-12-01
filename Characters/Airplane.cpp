#include "stdafx.h"
#include "Scenes/Scene.h"
#include "Utilities/Animator.h"
#include "Airplane.h"

Airplane::Airplane(Vector3 pos, Vector3 size, float rotation, wstring texturePath)
	: AnimationRect(pos, size, rotation, texturePath)
{
	animClips.push_back(new AnimationClip(L"MoveR", texture, 7, { 0, 0 }, { (float)texture->GetWidth(), (float)texture->GetHeight() }, false));
	animClips.push_back(new AnimationClip(L"MoveL", texture, 7, { 0, 0 }, { (float)texture->GetWidth(), (float)texture->GetHeight() }, true));
	animator = new Animator(animClips);
	animator->SetLoop(false);
}

Airplane::~Airplane()
{
}

void Airplane::Move(Vector3 position)
{
	Super::Move(position);

	if (position.x > 0)
	{
		animator->SetCurrentAnimClip(L"MoveR");
	}
	else if (position.x < 0)
	{
		animator->SetCurrentAnimClip(L"MoveL");
	}
}

void Airplane::Update()
{
	Super::Update();

	attackDelay += Time::Delta();
	bombDelay += Time::Delta();

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update();
	}

	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i]->Update();
	}
	
	for (int i = 0; i < bullets.size() ; i++)
	{
		if (bullets[i]->isDestoryed)
		{
			bullets.erase(bullets.begin() + i--);
		}
	}

	for (int i = 0; i < bombs.size(); i++)
	{
		if (bombs[i]->isDestoryed && bombs[i]->isExploded)
		{
			bombs.erase(bombs.begin() + i--);
		}
	}
}

void Airplane::Render()
{
	Super::Render();

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Render();
	}

	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i]->Render();
	}
}

void Airplane::Attack()
{
	if (bullets.empty() || bullets.back()->delayTime <= attackDelay)
	{
		bullets.push_back(new Bullet(Vector3(GetPosition().x, GetPosition().y + size.y / 2, GetPosition().z), Vector3(100, 100, 1), 0, L"_Textures/1945/Bullet.png"));
		attackDelay = 0.0f;
	}
}

void Airplane::Bomb()
{
	if (bombs.empty() || bombs.back()->delayTime <= bombDelay)
	{
		bombs.push_back(new class Bomb(GetPosition() + size / 2, Vector3(100, 100, 1), 0, L"_Textures/1945/Bomb.png"));
		bombDelay = 0.0f;
	}
}

void Airplane::Hit(Cannon* o)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (Math::RectIntersect(bullets[i], o)) // 오브젝트들이 총알과 충돌했다면 
		{
			bullets[i]->Hit(o);
		}
	}

	for (int i = 0; i < bombs.size(); i++)
	{
		if (Math::RectIntersect(bombs[i], o)) // 오브젝트들이 폭탄과 충돌했다면 
		{
			bombs[i]->Hit(o);
		}
	}
}
