#pragma once

struct VertexColor
{
	VertexColor() {}
	VertexColor(const Vector3& position, const Color& color)
		:position(position)
		, color(color)
	{}

	Vector3 position = { 0,0,0 };
	Color color = { 0,0,0,0 };
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 2;
};

struct VertexTexture
{
	VertexTexture() : position(0, 0, 0), uv(0, 0) {}
	VertexTexture(const Vector3& position, const Vector2& uv)
		:position(position)
		, uv(uv)
	{}

	Vector3 position;
	Vector2 uv;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 2;
};

struct VertexTextureColor
{
	VertexTextureColor() : position(0, 0, 0), color(0, 0, 0, 1), uv(0, 0){}
	VertexTextureColor(const Vector3& position, const Color& color, const Vector2& uv)
		: position(position), color(color), uv(uv) {}

	Vector3 position;
	Color color;
	Vector2 uv;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 3;
};

struct VertexTile
{
	VertexTile() : position(0, 0, 0), uv(0, 0), tileUV(0, 0), isTiled(false){}
	VertexTile(const Vector3& position, const Vector2& uv, const Vector2& tileUV, const bool& isTiled)
		: position(position), uv(uv), tileUV(tileUV), isTiled(isTiled)
	{}


	Vector3 position;
	Vector2 uv;
	Vector2 tileUV;
	bool isTiled;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 4;
};