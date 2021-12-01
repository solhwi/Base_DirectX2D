#include "stdafx.h"
#include "PixelShader.h"

PixelShader::~PixelShader()
{
	Clear();
}

void PixelShader::Create(wstring path, string entryName)
{
	this->path = path;
	this->entryName = entryName;

	CompileShader(path, entryName, "ps_5_0", &blob);
	HRESULT hr = Device->CreatePixelShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);
	Assert(hr);
}

void PixelShader::Clear()
{
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void PixelShader::SetShader()
{
	DC->PSSetShader(shader, nullptr, 0);
}
