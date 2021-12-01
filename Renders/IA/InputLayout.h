#pragma once

class InputLayout
{
public:
	InputLayout();
	~InputLayout();

	ID3D11InputLayout* GetResource() { return inputLayout; }

	void Create(D3D11_INPUT_ELEMENT_DESC* desc, const UINT& count, ID3DBlob* blob);
	void SetIA();

private:
	ID3D11InputLayout* inputLayout = nullptr;
};