#pragma once

class Scene11 : public Scene
{
public:
	Scene11();
	~Scene11();

	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	Airplane* player;

	vector<Cannon*> cannons;
};