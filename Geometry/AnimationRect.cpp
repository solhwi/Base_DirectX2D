#include "stdafx.h"
#include "AnimationRect.h"
#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size, float rotation, wstring texturePath)
	:Object(position, size, rotation, L"_Shaders/Animation.hlsl")
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

	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexTexture::descs, VertexTexture::count, VS->GetBlob());

	TransformVertices();

	//if(texturePath != L"")
	//	SetSRV(texturePath);

	texture = new Texture2D(texturePath);

	//CreateSamplerState
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));

		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.MaxAnisotropy = 16;
		desc.MinLOD = numeric_limits<float>::min();
		desc.MaxLOD = numeric_limits<float>::max();
		desc.MipLODBias = 0.0f;

		HRESULT hr = Device->CreateSamplerState(&desc, &SS);
		Assert(hr);
	}
}

AnimationRect::~AnimationRect()
{
	SAFE_RELEASE(SS);
	SAFE_DELETE(animator);

	for (auto a : animClips)
	{
		SAFE_DELETE(a);
	}
	
	SAFE_DELETE(texture);
}



void AnimationRect::SetShader(wstring shaderPath)
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

void AnimationRect::Move(Vector3 position)
{
	Super::Move(position);
	TransformVertices();
}

void AnimationRect::Update()
{
	Super::Update();
	animator->Update();

	D3D11_MAPPED_SUBRESOURCE subResource;

	DC->Map(VB->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		vertices[0].uv = Vector2(animator->GetCurrentFrame().x, animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y);
		vertices[1].uv = animator->GetCurrentFrame();
		vertices[2].uv = animator->GetCurrentFrame() + animator->GetTexelFrameSize();
		vertices[3].uv = Vector2(animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x, animator->GetCurrentFrame().y);
		memcpy(subResource.pData, vertices.data(), sizeof(VertexTexture) * vertices.size());
	}
	DC->Unmap(VB->GetResource(), 0);
}

void AnimationRect::Render()
{
	Super::Render();

	ID3D11ShaderResourceView* srv = texture->GetSRV();
	DC->PSSetShaderResources(0, 1, &srv);

	DC->PSSetSamplers(0, 1, &SS);

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, true);
}

void AnimationRect::GUI(int ordinal)
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
			//ChangeImageFunc();
		}
		if (ImGui::Button("ChangeShader", ImVec2(100, 30)))
		{
			//ChangeShaderFunc();
		}
		if (ImGui::InputText("InputText", text, sizeof(text), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			//SaveTextAsFile(text);
		}

		Super::GUI();

		ImGui::EndMenu();
	}
	else
	{
		SB->SetOutline(false);
	}
}

void AnimationRect::TransformVertices()
{
	D3DXVec3TransformCoord(&r.LT, &vertices[1].position, &world);
	D3DXVec3TransformCoord(&r.RB, &vertices[2].position, &world);
}