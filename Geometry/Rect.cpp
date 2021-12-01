#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation, Color color)
	:Object(position, size, rotation, L"_Shaders/VertexColor.hlsl", color)
{
	vertices.assign(4, VertexColor());
	vertices[0].position = Vector3(-0.5f, -0.5f, 0);
	//vertices[0].color = Red;
	vertices[1].position = Vector3(-0.5f, 0.5f, 0);
	//vertices[1].color = Red;
	vertices[2].position = Vector3(0.5f, -0.5f, 0);
	//vertices[2].color = Red;
	vertices[3].position = Vector3(0.5f, 0.5f, 0);
	//vertices[3].color = Red;

	indices = { 0, 1, 2, 2, 1, 3 };

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());

	TransformVertices();
}

Rect::~Rect()
{
}

void Rect::Move(Vector3 position)
{
	Super::Move(position);
	TransformVertices();
}

void Rect::Update()
{
	Super::Update();
}

void Rect::Render()
{
	Super::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, true);
}

void Rect::TransformVertices()
{
	D3DXVec3TransformCoord(&r.LT, &vertices[1].position, &world);
	D3DXVec3TransformCoord(&r.RB, &vertices[2].position, &world);
}
