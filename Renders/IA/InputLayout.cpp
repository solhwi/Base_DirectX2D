#include "stdafx.h"
#include "InputLayout.h"

InputLayout::InputLayout()
{
}

InputLayout::~InputLayout()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC * desc, const UINT & count, ID3DBlob * blob)
{
	if (!desc || !count || !blob)
		assert(false);

	HRESULT hr = Device->CreateInputLayout
	(
		desc,
		count,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&inputLayout
	);
	Assert(hr);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(inputLayout);
}
