///////////////////////////////VertexShader///////////////////////////////
cbuffer World : register(b0)
{
	matrix _world;
}

cbuffer ViewProjection : register(b1)
{
	matrix _view;
	matrix _proj;
}

cbuffer ColorBuffer : register(b2)
{
	float4 _color;
}

///////////////////////////////PixelShader///////////////////////////////

cbuffer SelectBuffer : register(b0)
{
	int _selection;
	bool _bOutline;
	float2 _textureSize;
}

cbuffer BlurBuffer : register(b1)
{
	uint _count;
}

cbuffer LocalBuffer : register(b2)
{
	float4 _localRect;
}

cbuffer GazyBuffer : register(b3)
{
    float _gazyAmount;
}