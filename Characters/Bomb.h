#pragma once

class AnimationRect;

class Bullet : public AnimationRect
{
public:
	Bullet();
	Bullet(Vector3 pos, Vector3 size, float rotation, wstring texturePath);
	virtual ~Bullet() {};

	void Update() override;
	virtual void Hit(Cannon* cannon);

	bool isDestoryed;

public:
	int damage;
	float delayTime;
	float lifeTime;
	float speed;
};

class Bomb : public Bullet
{
public:
	Bomb();
	Bomb(Vector3 pos, Vector3 size, float rotation, wstring texturePath);
	~Bomb() {};

	void Update() override;
	void Explode();

public:
	bool isExploding = false;
	bool isExploded = false;

	Texture2D* explosion;
};
