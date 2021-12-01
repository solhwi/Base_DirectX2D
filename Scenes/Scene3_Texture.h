#pragma once

class Scene3 : public Scene
{
public:
	Scene3();
	~Scene3();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override {}

private:
	RenderTexture* RTT = nullptr;
	TextureRect* texture = nullptr;
	Rect* rect = nullptr;
};