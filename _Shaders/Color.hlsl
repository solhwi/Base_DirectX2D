struct VertexInput // ���� 1���� �������ִ� ����
{
	float4 position : POSITION0; // 4��° �� 1(�ʱⰪ) - ��ġ, 0 - ����
	float4 color : COLOR0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float4 color : COLOR0;
};

//������ ������ �ʿ��� - 16byte������ ���������
//�������� 4x4�̹Ƿ� 16byte������ �������Ƿ� �Ű����� �ʿ䰡 ������
//16bytee������ �ȸ´ٸ� dummy�����͸� �߰��Ͽ� �������
cbuffer TransformBuffer : register(b0)
{
	matrix _world;
	matrix _view;
	matrix _proj;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, _world);
	output.position = mul(output.position, _view);
	output.position = mul(output.position, _proj);
	output.color = input.color;
	
	return output;
}

float4 PS(PixelInput input) : SV_Target
{
	return input.color;
}