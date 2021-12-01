struct VertexInput // 정점 1개가 가지고있는 정보
{
	float4 position : POSITION0; // 4번째 값 1(초기값) - 위치, 0 - 방향
	float4 color : COLOR0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float4 color : COLOR0;
};

//데이터 패팅이 필요함 - 16byte단위로 보내줘야함
//기존에는 4x4이므로 16byte단위로 보내지므로 신경을쓸 필요가 없었음
//16bytee단위로 안맞다면 dummy데이터를 추가하여 맞춰야함
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