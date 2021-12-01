#pragma once

#include "stdafx.h"

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer()
		:ShaderBuffer(&data, sizeof(WorldStruct))
	{
		D3DXMatrixIdentity(&data.world);
	}

	void SetWorld(Matrix world)
	{
		D3DXMatrixTranspose(&data.world, &world);
	}

	struct WorldStruct
	{
		Matrix world;
	};

private:
	WorldStruct data;
};

class ViewProjectionBuffer : public ShaderBuffer
{
public:
	ViewProjectionBuffer()
		:ShaderBuffer(&data, sizeof(ViewProjStruct))
	{
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.projection);
	}

	void SetView(Matrix view)
	{
		D3DXMatrixTranspose(&data.view, &view);
	}

	void SetProjection(Matrix projection)
	{
		D3DXMatrixTranspose(&data.projection, &projection);
	}

	struct ViewProjStruct
	{
		Matrix view;
		Matrix projection;
	};

private:
	ViewProjStruct data;
};

class ColorBuffer : public ShaderBuffer
{
public:
	ColorBuffer()
		:ShaderBuffer(&data, sizeof(Struct))
	{
		data.color = Color(0, 0, 0, 1);
	}

	void SetColor(Color color)
	{
		data.color = color;
	}

	struct Struct
	{
		Color color;
	};

private:
	Struct data;
};

class SelectBuffer : public ShaderBuffer
{
public:
	SelectBuffer()
		:ShaderBuffer(&data, sizeof(Struct))
	{}

	void SetSelection(int selection)
	{
		data.selection = selection;
	}

	void SetOutline(bool bOutline)
	{
		data.bOutline = bOutline;
	}

	struct Struct
	{
		int selection = 1;
		int bOutline = false;
		Vector2 textureSize = { WinMaxWidth, WinMaxHeight };
	};

private:
	Struct data;
};

class BlurBuffer : public ShaderBuffer
{
public:
	BlurBuffer()
		:ShaderBuffer(&data, sizeof(Struct))
	{}

	void SetCount(int count)
	{
		data.count = count;
	}

	struct Struct
	{
		UINT count = 0;
		Vector3 dummy;
	};

private:
	Struct data;
};

class LocalBuffer : public ShaderBuffer
{
public:
	LocalBuffer()
		:ShaderBuffer(&data, sizeof(Struct))
	{}

	void MoveLocalRect(Vector4 moveLocalRect)
	{
		data.localRect += moveLocalRect;
	}

	void SetLocalRect(Vector4 localRect)
	{
		data.localRect = localRect;
	}

	struct Struct
	{
		Vector4 localRect;
	};

private:
	Struct data;
};

class GazyBuffer : public ShaderBuffer
{
public:
	GazyBuffer() : ShaderBuffer(&data, sizeof(Struct)){}

	void SetGazy(float gazy)
	{
		data.gazy = gazy;
	}
	
	struct Struct
	{
		float gazy;
		Vector3 dummy;
	};

private:
	Struct data;
};