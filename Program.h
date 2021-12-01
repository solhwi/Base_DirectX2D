#pragma once

class Program
{
public:
	Program();
	~Program();

public:
	void Init();

	void SetGlobalBuffers();

	void Update();
	void PreRender();
	void Render();
	void PostRender();

private:
	shared_ptr<Scene> currentScene = nullptr;
	vector<shared_ptr<Scene>> sceneList;
};