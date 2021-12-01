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
	float4 result = 0;
	float4 color = srcTex0.Sample(samp, input.uv);
	
	float2 arr[8] =
	{
		float2(-1, -1), float2(0, -1), float2(1, -1),
		float2(-1, 0), float2(1, 0),
		float2(-1, 1), float2(0, 1), float2(1, 1),
	};
	
	[flatten]
	if (input.uv.x > _localRect.x / _textureSize.x
		&& input.uv.x < _localRect.z / _textureSize.x
		&& input.uv.y > _localRect.y / _textureSize.y
		&& input.uv.y < _localRect.w / _textureSize.y)
	{
		for (int blur = 0; blur < _count; blur++)
		{
			for (int i = 0; i < 8; i++)
			{
				float x = arr[i].x * (float) blur / _textureSize.x;
				float y = arr[i].y * (float) blur / _textureSize.y;

				float2 uv = input.uv + float2(x, y);
				color += srcTex0.Sample(samp, uv);
			}
		}
		
		color /= _count * 8 + 1;
		result = float4(color.rgb, 1);
	}
	else
	{
		result = color;
	}
	
	float border = 1.0f;
	
	if (_bOutline && (input.uv.x > 1.0f - border / 128 || input.uv.x < border / 128 || input.uv.y > 1.0f - border / 72 || input.uv.y < border / 72))
		result = float4(1, 1, 1, 1);
	
	return result;
}