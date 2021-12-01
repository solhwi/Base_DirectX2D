#include "stdafx.h"
#include "Scene2_Clock.h"

Scene2::Scene2()
{
}

Scene2::~Scene2()
{
	Destroy();
}

void Scene2::Init()
{
	clock = new Circle(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(WinMaxHeight / 2.3f, WinMaxHeight / 2.3f, 1), 0, 100, White);

	hour = new Line(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), WinMaxHeight / 4, 0, Red);
	minute = new Line(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), WinMaxHeight / 3, 0, Green);
	second = new Line(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), WinMaxHeight / 2.5f, 0, Blue);
}

void Scene2::Destroy()
{
	SAFE_DELETE(second);
	SAFE_DELETE(minute);
	SAFE_DELETE(hour);

	SAFE_DELETE(clock);
}

void Scene2::Update()
{
	GetLocalTime(&time);
	cout << time.wYear << "�� ";
	cout << time.wMonth << "�� ";
	cout << time.wDay << "�� ";
	switch (time.wDayOfWeek)
	{
	case 0:
		cout << "�Ͽ��� ";
		break;
	case 1:
		cout << "������ ";
		break;
	case 2:
		cout << "ȭ���� ";
		break;
	case 3:
		cout << "������ ";
		break;
	case 4:
		cout << "����� ";
		break;
	case 5:
		cout << "�ݿ��� ";
		break;
	case 6:
		cout << "����� ";
		break;
	default:
		break;
	}
	cout << time.wHour << "�� ";
	cout << time.wMinute << "�� ";
	cout << time.wSecond << "�� ";
	cout << time.wMilliseconds << "�и���";

	cout << endl;

	/*float secondRotation = 6 * time.wSecond + 6.0f / 1000 * time.wMilliseconds;
	float minuteRotation = 6 * time.wMinute + 6.0f / 360 * secondRotation;
	float hourRotation = 30 * (time.wHour % 12) + 30.0f / 360 * minuteRotation;

	hour->Rotation(90 - hourRotation);
	minute->Rotation(90 - minuteRotation);
	second->Rotation(90 - secondRotation);*/

	hour->Rotation(90 - time.wHour * 30.0f - time.wMinute * 30.0f / 60.0f - time.wSecond * 30.0f / 60.0f / 60.0f - time.wMilliseconds * 30.0f  / 60.0f / 60.0f / 1000.0f);
	minute->Rotation(90 - time.wMinute * 6.0f - time.wSecond * 6.0f / 60.0f - time.wMilliseconds * 6.0f / 60.0f / 1000.0f);
	second->Rotation(90 - time.wSecond * 6.0f - time.wMilliseconds * 6.0f / 1000.0f);

	clock->Update();
	hour->Update();
	minute->Update();
	second->Update();
}

void Scene2::Render()
{
	clock->Render();
	hour->Render();
	minute->Render();
	second->Render();
}
