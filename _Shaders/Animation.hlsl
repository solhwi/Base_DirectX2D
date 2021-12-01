#include "CBuffers.hlsl"

struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, _world);
	output.position = mul(output.position, _view);
	output.position = mul(output.position, _proj);
	
	output.uv = input.uv;
	
	return output;
}

Texture2D srcTex0 : register(t0);

SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	float4 color = srcTex0.Sample(samp, input.uv);
	
	float border = 1.0f;
	
	if(color.r > 0.85 && color.b > 0.85f) // ¸¶Á¨Å¸ ¼Ò°Å
    {
        discard;
    }
    
    if(color.g > 0.9f)
    {
        discard;
    }
       
    return color;
}