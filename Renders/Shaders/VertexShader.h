#pragma once

#include "IShader.h"

class VertexShader : public IShader
{
public:
	~VertexShader();

	ID3D11VertexShader* GetResource() { return shader; }
	ID3DBlob* GetBlob() { return blob; }

	void Create(wstring path, string entryName) override;
	void Clear() override;
	void SetShader() override;

private:
	ID3D11VertexShader* shader = nullptr;
	ID3DBlob* blob = nullptr;

};