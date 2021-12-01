#pragma once

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void Create(const vector<UINT>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResources() { return buffer;}
	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer;
	UINT stride;
	UINT offset;
	UINT count;
};