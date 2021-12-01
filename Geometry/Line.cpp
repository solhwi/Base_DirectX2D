#include "stdafx.h"
#include "Line.h"

Line::Line(Vector3 position, float length, float rotation, Color color)
	:Object(position, Vector3(length, 0, 0), rotation, L"_Shaders/VertexColor.hlsl", color)
{
	vertices.assign(2, VertexColor());
	vertices[0].position = Vector3(0, 0, 0);
	vertices[1].position = Vector3(1, 0, 0);

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());
}

Line::~Line()
{
}

void Line::Update()
{
	Super::Update();
}

void Line::Render()
{
	Super::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINELIST, false);
}
