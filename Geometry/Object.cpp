#include "stdafx.h"
#include "Object.h"

Object::Object(Vector3 position, Vector3 size, float rotation, wstring shaderPath, Color color)
	:position(position)
	, size(size)
	, rotation(rotation)
	, shaderPath(shaderPath)
	, color(color)
{
	VB = new VertexBuffer();
	IB = new IndexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	VS->Create(shaderPath, "VS");
	PS->Create(shaderPath, "PS");

	WB = new WorldBuffer();
	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&T);

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	WB->SetWorld(world);

	CB = new ColorBuffer();
	CB->SetColor(color);

	SB = new SelectBuffer();
	BB = new BlurBuffer();
	LB = new LocalBuffer();
	LB->SetLocalRect(Vector4(100, 100, 400, 400));

	right = Vector3(R._11, R._12, R._13);
	up = Vector3(R._21, R._22, R._23);
}

Object::~Object()
{
	SAFE_DELETE(LB);
	SAFE_DELETE(BB);
	SAFE_DELETE(SB);

	SAFE_DELETE(CB);

	SAFE_DELETE(WB);

	SAFE_DELETE(IL);

	SAFE_DELETE(PS);
	SAFE_DELETE(VS);

	SAFE_DELETE(IB);
	SAFE_DELETE(VB);
}

void Object::Move(Vector3 position)
{
	this->position += position;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);
	world = S * R * T;

	WB->SetWorld(world);
}

void Object::MoveLocalRect(Vector4 localMove)
{
	LB->MoveLocalRect(localMove);
}

void Object::Rotation(float rotation)
{
	this->rotation = rotation;
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(this->rotation));

	world = S * R * T;
	WB->SetWorld(world);
}

void Object::ScaleUp(Vector3 size)
{
	this->size = size;
	D3DXMatrixScaling(&S, size.x, size.y, size.z);

	world = S * R * T;
	WB->SetWorld(world);
}

void Object::Update()
{
	if (Keyboard::Get()->Down(VK_01))
	{
		SB->SetSelection(1);
		BB->SetCount(2);
	}
	else if (Keyboard::Get()->Down(VK_02))
	{
		SB->SetSelection(2);
		BB->SetCount(4);
	}
	else if (Keyboard::Get()->Down(VK_03))
	{
		SB->SetSelection(3);
		BB->SetCount(8);
	}
	else if (Keyboard::Get()->Down(VK_04))
	{
		SB->SetSelection(4);
		BB->SetCount(16);
	}
	else if (Keyboard::Get()->Down(VK_05))
	{
		SB->SetSelection(5);
		BB->SetCount(32);
	}
	CB->SetColor(color);

	right = Vector3(R._11, R._12, R._13);
	up = Vector3(R._21, R._22, R._23);

}

void Object::Render()
{
	VB->SetIA();
	if(indices.size() > 0)
		IB->SetIA();
	IL->SetIA();
	//DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	WB->SetVSBuffer(0);
	CB->SetVSBuffer(2);

	VS->SetShader();

	SB->SetPSBuffer(0);
	BB->SetPSBuffer(1);
	LB->SetPSBuffer(2);
	PS->SetShader();

	//DC->DrawIndexed(6, 0, 0);
}

void Object::GUI()
{
	ImGui::SliderFloat3("Translation", position, 0, WinMaxWidth, "%.2f");
	ImGui::SliderFloat3("Size", size, 1, WinMaxWidth, "%.2f");
	ImGui::SliderAngle("Rotation", &rotation); // 반환값이 radian값이므로 아래에서 radian값으로 변경할 필요없음

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, -rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	WB->SetWorld(world);
}

void Object::DrawCall(D3D11_PRIMITIVE_TOPOLOGY topology, bool indexed)
{
	DC->IASetPrimitiveTopology(topology);

	if (indexed)
		DC->DrawIndexed(IB->GetCount(), 0, 0);
	else
		DC->Draw(VB->GetCount(), 0);
}