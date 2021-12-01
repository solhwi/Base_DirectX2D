#include "stdafx.h"
#include "Scenes/SceneList.h"
#include "Program.h"

Program::Program()
{
	Camera::Create();
}

Program::~Program()
{
	Camera::Delete();
}

void Program::Init()
{
	sceneList.push_back(make_shared<Scene1>());
	//sceneList.push_back(make_shared<Scene2>());
	//sceneList.push_back(make_shared<Scene3>());
	//sceneList.push_back(make_shared<Scene4>());
	//sceneList.push_back(make_shared<Scene5>());
	//sceneList.push_back(make_shared<Scene6>());
	sceneList.push_back(make_shared<Scene10>());
	sceneList.push_back(make_shared<Scene12>());

	currentScene = sceneList.front();
	currentScene->Init();
	Camera::Get()->Move(Vector3(0, 0, 0));
}

void Program::SetGlobalBuffers()
{

}

void Program::Update()
{
	if (Keyboard::Get()->Down(VK_F1))
	{
		currentScene->Destroy();

		currentScene = sceneList[0];
		currentScene->Init();
		Camera::Get()->Move(Vector3(0, 0, 0));

	}
	else if (Keyboard::Get()->Down(VK_F2))
	{
		currentScene->Destroy();

		currentScene = sceneList[1];
		currentScene->Init();
		Camera::Get()->Move(Vector3(0, 0, 0));
	}

	Camera::Get()->Update();
	currentScene->Update();
}

void Program::PreRender()
{
	currentScene->PreRender();
}

void Program::Render()
{
	Camera::Get()->Render();
	currentScene->Render();
}

void Program::PostRender()
{
	currentScene->PostRender();
	Gui::Get()->PrintFrame();
}
