#pragma once

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override {}
	void Render() override;
	void PostRender() override {}

private:
	SYSTEMTIME time;

	Circle* clock = nullptr;

	Line* hour = nullptr;
	Line* minute = nullptr;
	Line* second = nullptr;
};