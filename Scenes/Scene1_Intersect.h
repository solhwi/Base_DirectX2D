#pragma once

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override {}
	void Render() override;
	void PostRender() override {}

private:
	Rect* rect = nullptr;
	Rect* rect2 = nullptr;


};