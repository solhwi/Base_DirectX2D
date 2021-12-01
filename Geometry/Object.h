#pragma once

struct RectEdges
{
	Vector3 LT;
	Vector3 RB;
};

class Object
{
public:
	Object(Vector3 position, Vector3 size, float rotation, wstring shaderPath, Color color = Red);
	virtual ~Object();

	virtual void Move(Vector3 position);
	void MoveLocalRect(Vector4 localMove);
	void Rotation(float rotation);
	void ScaleUp(Vector3 size);

	virtual void Update();
	virtual void Render();

	void GUI();

	RectEdges GetTransformCoord() { return r; }
	void SetIntersect(bool bIntersect) { this->bIntersect = bIntersect; }
	
	Vector3 GetPosition() { return position; }
	Vector3 GetScale() { return size; }
	
	void SetColor(Color color) { this->color = color; CB->SetColor(color); }

	Vector3 Right() { return right; }
	Vector3 Up() { return up; }

protected:
	void DrawCall(D3D11_PRIMITIVE_TOPOLOGY topology, bool indexed);

	vector<UINT> indices;
	InputLayout* IL = nullptr;

	VertexBuffer* VB = nullptr;
	IndexBuffer* IB = nullptr;

	VertexShader* VS = nullptr;
	PixelShader* PS = nullptr;

	wstring shaderPath = L"";

	WorldBuffer* WB = nullptr;
	Matrix world, S, R, T;

	Vector3 position, size;
	float rotation;

	ColorBuffer* CB = nullptr;
	Color color;

	RectEdges r;
	bool bIntersect = false;

	SelectBuffer* SB = nullptr;
	BlurBuffer* BB = nullptr;
	LocalBuffer* LB = nullptr;

	Vector3 right = Vector3(1, 0, 0);
	Vector3 up = Vector3(0, 1, 0);
};