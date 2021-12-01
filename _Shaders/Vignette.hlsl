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
	
	float2 dist = input.uv - 0.5f;
	
	float border = 1.0f;
	
	if (_selection == 1)
		color = srcTex0.Sample(samp, input.uv);
	else if (_selection == 2)
		color.rgb *= 1 - dot(dist, dist) * 5;
	
	if (_bOutline && (input.uv.x > 1.0f - border / 128 || input.uv.x < border / 128 || input.uv.y > 1.0f - border / 72 || input.uv.y < border / 72))
	{
		color = float4(1, 1, 1, 1);
	}
	
	return color;
}