#pragma once

class AnimationRect;

class Airplane : public AnimationRect
{
public:
	Airplane(Vector3 pos, Vector3 size, float rotation, wstring texturePath = L"");
	~Airplane();

	void Move(Vector3 position) override;
	void Update() override;
	void Render() override;
	void Attack();
	void Bomb();

	void Hit(Cannon* o);

private:
	float attackDelay = 0.0f;
	float bombDelay = 0.0f;

	vector<class Bullet*> bullets;
	vector<class Bomb*> bombs;
};