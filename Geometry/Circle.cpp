#include "stdafx.h"
#include "Circle.h"

Circle::Circle(Vector3 position, Vector3 size, float rotation, int segments, Color color)
	: Object(position, size, rotation, L"_Shaders/VertexColor.hlsl", color)
	, segments(segments)
{
	vertices.assign(segments + 1, VertexColor());
	{
		for (int i = 0; i <= segments; i++)
		{
			float t = 2 * (float)D3DX_PI * i / segments;

			vertices[i].position = Vector3(cosf(t), -sinf(t), 0);
		}
	}

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());
}

Circle::~Circle()
{
}

void Circle::Update()
{
	Super::Update();
}

void Circle::Render()
{
	Super::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, false);
}
