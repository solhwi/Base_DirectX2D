#include "stdafx.h"
#include "Items.h"

// TextureRect(Vector3 position, Vector3 size, float rotation, wstring texturePath = L"");

//Bullet::Bullet(Vector3 CannonPos, float power)
//	: TextureRect(CannonPos, Vector3(100, 100, 1), 0, L"_Textures/bk.bmp")
//{
//	this->power = power;
//	currDir = Vector3(power, abs(power), 0); // 파워를 통해 첫 벡터를 계산한다.
//	lifeTime = 3.0f;
//	isExploded = false;
//	explodeSize = Vector3(size.x * 1.5, size.y * 1.5, size.z * 1.5);
//}
//
//void Bullet::Update()
//{
//	lifeTime -= Time::Delta();
//
//	if (lifeTime < 0.0f && !isExploded)
//	{
//		Explode();
//	}
//	else
//	{
//		Move(currDir);
//	}
//	
//	ChangeDir();
//}
//
//void Bullet::Explode()
//{
//	float explodeSpeed = 15.0f * Time::Delta();
//
//	if (size.x >= explodeSize.x)
//	{
//		isExploded = true;
//	}
//
//	size = Vector3(size.x + explodeSpeed, size.y + explodeSpeed, size.z + explodeSpeed);
//	ScaleUp(size);
//}
//
//void Bullet::ChangeDir()
//{
//	if (position.y < size.y / 2)
//	{
//		currDir.y = -currDir.y;
//	}
//	else
//	{
//		currDir.y -= 9.8f * Time::Delta();
//	}
//
//	if (position.x < size.x / 2 || position.x > WinMaxWidth - size.x / 2)
//	{
//		currDir.x = -currDir.x;
//	}
//}

Cannon::Cannon(Vector3 pos, Vector3 size, float rotation, wstring texturePath)
	: TextureRect(pos, size, rotation, L"_Textures/Tree.png")
{
}

void Cannon::Hit(int damage)
{
	hpPoint -= damage;

	if (hpPoint <= 0)
	{
		isDestroyed = true;
	}
}


Gazy::Gazy(Vector3 pos)
	: TextureRect(pos, Vector3(200, 50, 1), 0, L"_Textures/forest1.png")
{
	SetShader(L"_Shaders/Gazy.hlsl");
	GB = new GazyBuffer();
}


void Gazy::Update()
{
	GB->SetGazy(gazyAmount);
	Super::Update();
}

void Gazy::Render()
{
	GB->SetPSBuffer(3);
	Super::Render();
}

void Gazy::SetGazy(float delta)
{
	if (gazyAmount + delta * fillRate > 1.0f)
	{
		gazyAmount = 0.0f;
	}
	else
	{
		gazyAmount += delta * fillRate;
	}
}
