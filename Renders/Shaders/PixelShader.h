#pragma once

#include "IShader.h"

class PixelShader : public IShader
{
public:
	~PixelShader();

	ID3D11PixelShader* GetResource() { return shader; }
	ID3DBlob* GetBlob() { return blob; }

	void Create(wstring path, string entryName) override;
	void Clear() override;
	void SetShader() override;

private:
	ID3D11PixelShader* shader;
	ID3DBlob* blob;
};