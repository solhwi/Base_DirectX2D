#pragma once

class Scene4 : public Scene
{
public:
	Scene4();
	~Scene4();

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