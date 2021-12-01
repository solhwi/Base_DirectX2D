#include "stdafx.h"
#include "RenderTexture.h"

RenderTexture::RenderTexture()
{
}

RenderTexture::~RenderTexture()
{
	SAFE_RELEASE(shaderResourceView);
	SAFE_RELEASE(renderTargetView);
	SAFE_RELEASE(renderTargetTexture);
}

void RenderTexture::Initialize()
{
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	HRESULT hr;

	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&renderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	textureDesc.Width = WinMaxWidth;
	textureDesc.Height = WinMaxHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	hr = Device->CreateTexture2D(&textureDesc, nullptr, &renderTargetTexture);
	Assert(hr);

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	hr = Device->CreateRenderTargetView(renderTargetTexture, &renderTargetViewDesc, &renderTargetView);
	Assert(hr);

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	hr = Device->CreateShaderResourceView(renderTargetTexture, &shaderResourceViewDesc, &shaderResourceView);
	Assert(hr);
}

void RenderTexture::RenderToTexture()
{
	DC->OMSetRenderTargets(1, &renderTargetView, nullptr);
	DC->ClearRenderTargetView(renderTargetView, Graphics::Get()->GetClearColor());
}

void RenderTexture::SaveTexture(const wstring & path)
{
	HRESULT hr = D3DX11SaveTextureToFile
	(
		DC,
		renderTargetTexture,
		D3DX11_IFF_PNG,
		path.c_str()
	);
	Assert(hr);
}
