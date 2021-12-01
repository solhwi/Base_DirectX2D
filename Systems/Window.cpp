#include "stdafx.h"
#include "Window.h"
#include "Program.h"

WinDesc Window::desc;
Program* Window::program = nullptr;

Window::Window(WinDesc desc)
{
	WNDCLASSEX wndClass; 
	ZeroMemory(&wndClass, sizeof(wndClass)); 

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW); 
	wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = desc.instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpszMenuName = nullptr;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	desc.handle = CreateWindowEx 
	(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(),
		desc.AppName.c_str(),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_TABSTOP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		(HMENU)nullptr,
		desc.instance,
		nullptr
	);

	RECT rect = { 0,0,(LONG)desc.width, (LONG)desc.height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	MoveWindow
	(
		desc.handle,
		centerX,
		centerY,
		rect.right - rect.left,
		rect.bottom - rect.top,
		true
	);

	ShowWindow(desc.handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.handle);
	SetFocus(desc.handle);

	ShowCursor(true);

	Window::desc = desc;

}

Window::~Window()
{
	DestroyWindow(desc.handle);
	UnregisterClass(desc.AppName.c_str(), desc.instance);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	Graphics::Create();

	Keyboard::Create();
	Mouse::Create();
	Time::Create();

	Gui::Create();

	Time::Get()->Start();

	program = new Program();
	program->Init();

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Time::Get()->Update();
			if (ImGui::IsMouseHoveringAnyWindow() == false)
			{
				Keyboard::Get()->Update();
				Mouse::Get()->Update();
			}
			Gui::Get()->Update();

			program->Update();
			
			//·»´õ¸µ ¿µ¿ª
			program->PreRender();
			Graphics::Get()->Begin();
			{
				program->Render();
				program->PostRender();
				Gui::Get()->Render();
			}
			Graphics::Get()->End();
		}
	}

	SAFE_DELETE(program);

	Gui::Delete();

	Time::Delete();
	Mouse::Delete();
	Keyboard::Delete();

	Graphics::Delete();

	return msg.wParam;
}

HWND handle;

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	Mouse::Get()->InputProc(message, wParam, lParam);

	if (Gui::Get()->MsgProc(handle, message, wParam, lParam))
		return true;

	if (message == WM_CREATE)
	{
		::handle = handle;
	}


	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
