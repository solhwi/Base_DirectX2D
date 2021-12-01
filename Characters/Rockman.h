#pragma once

class AnimationRect;

class Rockman : public AnimationRect
{
public:
	Rockman(Vector3 pos, Vector3 size, float rotation, wstring texturePath = L"");
	~Rockman();

	void Move(Vector3 position) override;
	

private:
};