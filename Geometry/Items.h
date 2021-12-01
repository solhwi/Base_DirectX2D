#pragma once
//
//class Bullet : public TextureRect
//{
//public:
//	Bullet(Vector3 CannonPos, float power);
//
//	void Update() override;
//	void Explode();
//	void ChangeDir();
//
//	bool isExploded;
//	int damage = 20;
//		
//private:
//	float power;
//	float lifeTime;
//
//	Vector3 currDir;
//	Vector3 explodeSize;
//
//};

class Cannon : public TextureRect
{
public:
	Cannon(Vector3 position, Vector3 size, float rotation, wstring texturePath = L"");

	Vector3 GetPos() { return position; }
	void Hit(int damage);

	bool isDestroyed = false;

private:
	int hpPoint = 100;
};

class Gazy : public TextureRect
{
public:
	Gazy(Vector3 pos);

	void Update() override; 
	void Render() override;
	void SetGazy(float delta); // 게이지를 채움

	float GetGazyAmount() { return gazyAmount; }

private:
	float gazyAmount = 0.0f; // 1까지 가질 수 있는 값
	float fillRate = 1.0f; 

	GazyBuffer* GB = nullptr;
};