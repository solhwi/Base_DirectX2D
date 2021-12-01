#include "stdafx.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring texturePath)
	:Object(position, size, rotation, L"_Shaders/VertexTexture.hlsl")
	, texturePath(texturePath)
{
	vertices.assign(4, VertexTexture());
	vertices[0].position = Vector3(-0.5f, -0.5f, 0);
	vertices[0].uv = Vector2(0.0f, 1.0f);

	vertices[1].position = Vector3(-0.5f, 0.5f, 0);
	vertices[1].uv = Vector2(0.0f, 0.0f);

	vertices[2].position = Vector3(0.5f, -0.5f, 0);
	vertices[2].uv = Vector2(1.0f, 1.0f);

	vertices[3].position = Vector3(0.5f, 0.5f, 0);
	vertices[3].uv = Vector2(1.0f, 0.0f);

	indices = { 0, 1, 2, 2, 1, 3 };

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexTexture::descs, VertexTexture::count, VS->GetBlob());

	TransformVertices();

	if(texturePath != L"")
		SetSRV(texturePath);
}

TextureRect::~TextureRect()
{
	SAFE_RELEASE(nullView);
	SAFE_RELEASE(srv);
}

void TextureRect::SetSRV(wstring path)
{
	this->texturePath = path;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		Device,
		path.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	Assert(hr);
}

void TextureRect::SetShader(wstring shaderPath)
{
	this->shaderPath = shaderPath;

	if (VS)
	{
		VS->Clear();
		VS->Create(shaderPath, "VS");
	}

	if (PS)
	{
		PS->Clear();
		PS->Create(shaderPath, "PS");
	}
}

void TextureRect::Move(Vector3 position)
{
	Super::Move(position);
	TransformVertices();
}

void TextureRect::Update()
{
	Super::Update();
}

void TextureRect::Render()
{
	Super::Render();

	if (srv)
		DC->PSSetShaderResources(0, 1, &srv);

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, true);

	if (srv)
		DC->PSSetShaderResources(0, 1, &nullView);
}

void TextureRect::GUI(int ordinal)
{
	string objName = "TextureRect" + to_string(ordinal);
	string imgName = "Image : " + String::ToString(Path::GetFileName(texturePath));
	string shaderName = "Shader : " + String::ToString(Path::GetFileName(shaderPath));

	if (ImGui::BeginMenu(objName.c_str()))
	{
		SB->SetOutline(true);

		ImGui::Text(objName.c_str());
		ImGui::Text(imgName.c_str());
		ImGui::Text(shaderName.c_str());

		if (ImGui::Button("ChangeImage", ImVec2(100, 30)))
		{
			ChangeImageFunc();
		}
		if (ImGui::Button("ChangeShader", ImVec2(100, 30)))
		{
			ChangeShaderFunc();
		}
		if (ImGui::InputText("InputText", text, sizeof(text), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			SaveTextAsFile(text);
		}

		Super::GUI();

		ImGui::EndMenu();
	}
	else
	{
		SB->SetOutline(false);
	}
}

void TextureRect::TransformVertices()
{
	D3DXVec3TransformCoord(&r.LT, &vertices[1].position, &world);
	D3DXVec3TransformCoord(&r.RB, &vertices[2].position, &world);
}

void TextureRect::ChangeImageFunc(const wstring & path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TextureRect::ChangeImageFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ImageFilter, L"_Textures/", func, handle);
	}
	else
	{
		SetSRV(path);
	}
}

void TextureRect::ChangeShaderFunc(const wstring & path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TextureRect::ChangeShaderFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ShaderFilter, L"_Shaders/", func, handle);
	}
	else
	{
		SetShader(path);
	}
}

void TextureRect::SaveTextAsFile(const string & text, const wstring & path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TextureRect::SaveTextAsFile, this, text, placeholders::_1);
		Path::SaveFileDialog(L"", Path::TextFilter, L"./", func, handle);
	}
	else
	{
		ofstream writeFile(path.c_str());
		if (writeFile.is_open())
		{
			writeFile << text << endl;
			writeFile.clear();
		}
		writeFile.close();
	}
}
