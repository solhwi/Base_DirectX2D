#pragma once

class Scene8 : public Scene
{
public:
	Scene8();
	~Scene8();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	SoundSystem* BGSound = nullptr;
	SoundSystem* EffSound = nullptr;
};