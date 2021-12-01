#pragma once

class Scene12 : public Scene
{
public:
	Scene12();
	~Scene12();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	TileMap* tileMap;
};