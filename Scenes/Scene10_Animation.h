#pragma once

class Scene10 : public Scene
{
public:
	Scene10();
	~Scene10();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	TextureRect* background = nullptr;
	Texture2D* mapTex = nullptr;
	Rockman* rockman;
};