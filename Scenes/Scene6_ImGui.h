#pragma once

class Scene6 : public Scene
{
public:
	Scene6();
	~Scene6();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	vector<wstring> paths;
	vector<TextureRect*> trVec;
};