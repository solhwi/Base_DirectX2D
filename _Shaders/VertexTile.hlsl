#include "CBuffers.hlsl"

struct VertexInput
{
	float4 position : POSITION0;
    float4 color : COLOR0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
    float4 color : COLOR0;
	float2 uv : TEXCOORD0;
};


PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, _world);
	output.position = mul(output.position, _view);
	output.position = mul(output.position, _proj);
	
    output.color = input.color;
	output.uv = input.uv;
	
	return output;
}

Texture2D tileTex : register(t0);

SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = tileTex.Sample(samp, input.uv);
	
	float border = 1.0f;
	
    if(input.uv.x > 0 || input.uv.y > 0)
    {
        return color;
    }
    else
    {
        return input.color;
    }
}