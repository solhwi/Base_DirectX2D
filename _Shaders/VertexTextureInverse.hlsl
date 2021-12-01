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
	float4 color = 0;
	
	float border = 1.0f;
	
	if (_selection == 1)
		color = srcTex0.Sample(samp, input.uv);
	else if (_selection == 2)
	{
		color = srcTex0.Sample(samp, float2(1 - input.uv.x, input.uv.y));
	}
	else if (_selection == 3)
	{
		float4 l = srcTex0.Sample(samp, input.uv);
		float4 r = srcTex0.Sample(samp, float2(input.uv.x - 0.5f, input.uv.y));
		
		if (input.uv.x < 0.5f)
			color = l;
		else
			color = r;
		
		if (input.uv.x > 0.499f && input.uv.x < 0.501f)
			color = float4(1, 1, 1, 1);
	}
	else if (_selection == 4)
	{
		float4 lt = srcTex0.Sample(samp, input.uv * 2);
		float4 rt = srcTex0.Sample(samp, 2 * float2(1 - input.uv.x, input.uv.y));
		float4 lb = srcTex0.Sample(samp, 2 * float2(input.uv.x, 1 - input.uv.y));
		float4 rb = srcTex0.Sample(samp, 2 * (1 - input.uv));
		
		if (input.uv.x < 0.5f && input.uv.y < 0.5f)
			color = lt;
		else if (input.uv.x > 0.5f && input.uv.y < 0.5f)
			color = rt;
		else if (input.uv.x < 0.5f && input.uv.y > 0.5f)
			color = lb;
		else
			color = rb;
		
		if ((input.uv.x > 0.499f && input.uv.x < 0.501f) || (input.uv.y > 0.498f && input.uv.y < 0.502f))
			color = float4(1, 1, 1, 1);
	}
	else if (_selection == 5)
	{
		if ((input.uv.x > 0.499f && input.uv.x < 0.501f) || (input.uv.y > 0.498f && input.uv.y < 0.502f)
			|| ((input.uv.x >= 0.5f) && (input.uv.y >= 0.5f) && ((input.uv.x > 0.749f && input.uv.x < 0.751f) || (input.uv.y > 0.748f && input.uv.y < 0.752f))))
			color = float4(1, 1, 1, 1);
		else
		{
			input.uv.x *= 2;
			input.uv.y *= 2;
			if (input.uv.x > 1 && input.uv.y > 1)
			{
				input.uv.x *= 2;
				input.uv.y *= 2;
				input.uv.x -= 2;
				input.uv.y -= 2;
				if (input.uv.x > 1)
				{
					input.uv.x = 2 - input.uv.x;
				}
				if (input.uv.y > 1)
				{
					input.uv.y = 2 - input.uv.y;
				}
			}
			else if (input.uv.x > 1)
			{
				input.uv.x = 2 - input.uv.x;
			}
			else if (input.uv.y > 1)
			{
				input.uv.y = 2 - input.uv.y;
			}
			color = srcTex0.Sample(samp, input.uv);
		}
	}
	
	if (_bOutline && (input.uv.x > 1.0f - border / 128 || input.uv.x < border / 128 || input.uv.y > 1.0f - border / 72 || input.uv.y < border / 72))
	{
		color = float4(1, 1, 1, 1);
	}
	return color;
}