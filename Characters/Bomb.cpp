#include "stdafx.h"
#include "Bomb.h"
#include "Scenes/Scene.h"
#include "Utilities/Animator.h"

// ---- Bullet ---- // 

Bullet::Bullet(Vector3 pos, Vector3 size, float rotation, wstring texturePath)
	: AnimationRect(pos, size, rotation, texturePath)
{
	animClips.push_back(new AnimationClip(L"Bullet", texture, 3, { 0, 0 }, { (float)texture->GetWidth(), (float)texture->GetHeight() }, false));
	//animClips.push_back(new AnimationClip(L"MoveL", texture, 3, { 0, 0 }, { (float)texture->GetWidth(), (float)texture->GetHeight() }, true));
	animator = new Animator(animClips);
	animator->SetLoop(false);
	animator->SetCurrentAnimClip(L"Bullet");

	lifeTime = 3.0f;
	delayTime = 0.33f;
	speed = 300.0f;
	damage = 10.0f;
}

void Bullet::Update()
{
	Super::Update();

	if (lifeTime < 0.0f) isDestoryed = true;
	else lifeTime -= Time::Delta();

	if(!isDestoryed) Move(Vector3(0, speed, 0) * Time::Delta());
}

void Bullet::Hit(Cannon* cannon)
{
	cannon->Hit(damage); // 캐논에게 데미지를 줍니다.
	isDestoryed = true; // 본인은 파괴됩니다.
}

// ---- Bomb ---- // 

Bomb::Bomb(Vector3 pos, Vector3 size, float rotation, wstring texturePath)
	: Bullet(pos, size, rotation, texturePath)
{
	animClips.push_back(new AnimationClip(L"Bomb", texture, 8, { 0, 0 }, { (float)texture->GetWidth(), (float)texture->GetHeight() / 4 }, true));

	explosion = new Texture2D(L"_Textures/1945/Explosion.png");

	animClips.push_back(new AnimationClip(L"Explosion", explosion, 8, { 0, 0 }, { (float)explosion->GetWidth(), (float)explosion->GetHeight() }, false));
	//animClips.push_back(new AnimationClip(L"MoveL", texture, 3, { 0, 0 }, { (float)texture->GetWidth(), (float)texture->GetHeight() }, true));
	animator = new Animator(animClips);
	animator->SetLoop(false);
	animator->SetCurrentAnimClip(L"Bomb");

	lifeTime = 3.0f;
	delayTime = 1.5f;
	speed = 200.0f;
	damage = 100.0f;
}

void Bomb::Update()
{
	Super::Update();

	if (!isExploded && isDestoryed)
	{
		isExploding = true;
		//	SetSRV(explosion->GetSRV());
		animator->SetCurrentAnimClip(L"Explosion");
		Explode();
	}
	else
	{
		//SetSRV(texture->GetSRV());
	}
}

void Bomb::Explode()
{
	if (animator->currentAnimClipEnded)
	{
		isExploded = true;
	}
}
