#pragma once

class Scene5 : public Scene
{
public:
	Scene5();
	~Scene5();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override {}

private:
	Rect* rect = nullptr;
	Rect* rect2 = nullptr;

	RenderTexture* RTT = nullptr;
	TextureRect* texture = nullptr;
};