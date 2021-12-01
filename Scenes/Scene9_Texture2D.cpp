#include "stdafx.h"
#include "Scene9_Texture2D.h"

Scene9::Scene9()
{
	tex2D = new Texture2D(L"_Textures/Tree.png");
	vector<Color> color;
	DirectX::TexMetadata metaData;
	tex2D->GetImageInfo(&metaData);
	tex2D->ReadPixel(metaData.format, &color);

	ID3D11Texture2D* originalTex;
	tex2D->GetSRV()->GetResource((ID3D11Resource**)&originalTex);
	tex2D->SaveFile(L"Test.png", originalTex, color, tex2D->GetWidth(), tex2D->GetHeight());
}

Scene9::~Scene9()
{
	Destroy();
}

void Scene9::Init()
{
	textureRect = new TextureRect(Vector3(100, 100, 0), Vector3(100, 100, 1), 0);
	textureRect->SetSRV(tex2D->GetSRV());
}

void Scene9::Destroy()
{
	SAFE_DELETE(textureRect);
	SAFE_DELETE(tex2D);
}

void Scene9::Update()
{

}

void Scene9::PreRender()
{
}

void Scene9::Render()
{
	textureRect->Render();
}

void Scene9::PostRender()
{
}
