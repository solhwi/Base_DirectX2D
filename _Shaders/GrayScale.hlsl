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
	float3 grayscale = 0;
	float3 sepia = 0;
	
	float border = 1.0f;
	
	if (_selection == 1)
		color = srcTex0.Sample(samp, input.uv);
	else if (_selection == 2)
	{
		grayscale = (color.r + color.g + color.b) / 3.0f;
		color = float4(grayscale, 1);
	}
	else if (_selection == 3)
	{
		grayscale = dot(color.rgb, float3(0.299, 0.587, 0.114));
		color = float4(grayscale, 1);
	}
	else if (_selection == 4)
	{
		sepia.r = dot(color.rgb, float3(0.393, 0.769, 0.189));
		sepia.g = dot(color.rgb, float3(0.349, 0.686, 0.168));
		sepia.b = dot(color.rgb, float3(0.272, 0.534, 0.131));
		color = float4(sepia, 1);
	}
	if (_bOutline && (input.uv.x > 1.0f - border / 128 || input.uv.x < border / 128 || input.uv.y > 1.0f - border / 72 || input.uv.y < border / 72))
	{
		color = float4(1, 1, 1, 1);
	}
	return color;
}