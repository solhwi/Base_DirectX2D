#include "stdafx.h"
#include "VertexShader.h"

VertexShader::~VertexShader()
{
	Clear();
}

void VertexShader::Create(wstring path, string entryName)
{
	this->path = path;
	this->entryName = entryName;

	CompileShader(path, entryName, "vs_5_0", &blob);
	HRESULT hr = Device->CreateVertexShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);
	Assert(hr);
}

void VertexShader::Clear()
{
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void VertexShader::SetShader()
{
	DC->VSSetShader(shader, nullptr, 0);
}
