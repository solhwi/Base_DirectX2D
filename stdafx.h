#pragma once
#define no_init_all deprecated

#define NOMINMAX

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#define Super __super

#include <Windows.h>
#include <assert.h>

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <fstream>

using namespace std;

#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment(lib, "ImGui/ImGui.lib")

#pragma comment(lib, "FMOD/fmodex_vc.lib")

#include "DirectTex/DirectXTex.h"
#pragma comment(lib, "DirectTex/DirectXTex.lib")

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;
typedef D3DXMATRIX Matrix;
typedef D3DXCOLOR Color;

#include "Utilities/Singleton.h"
#include "Systems/Graphics.h"

#define DC Graphics::Get()->GetDC()
#define Device Graphics::Get()->GetDevice()

#define Assert(p) assert(SUCCEEDED(p))

#define WinMaxWidth 1280
#define WinMaxHeight 720

#define SAFE_DELETE(p) { if(p) { delete(p); p = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p); p = nullptr; } }
#define SAFE_RELEASE(p) { if(p) { p->Release(); p = nullptr; } }

#define Red Color(1, 0, 0, 1)
#define Green Color(0, 1, 0, 1)
#define Blue Color(0, 0, 1, 1)
#define Black Color(0, 0, 0, 1)
#define White Color(1, 1, 1, 1)
#define Yellow Color(1, 1, 0, 1)
#define Magenta Color(1, 0, 1, 1)
#define Cyan Color(0, 1, 1, 1)

extern HWND handle;

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"
#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/inputLayout.h"
#include "Renders/Resources/VertexType.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"

#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
#include "Systems/Time.h"
#include "Systems/GUI/Gui.h"
#include "Systems/Camera.h"

#include "Utilities/Math.h"

#include "Utilities/String.h"
#include "Utilities/Path.h"
#include "Utilities/FileStream.h"

#include "Scenes/Scene.h"