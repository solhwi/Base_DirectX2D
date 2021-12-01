#pragma once

class Camera : public Singleton<Camera>
{
public:
	friend class Singleton<Camera>;

	void Update();
	void Render();

	void Move(Vector3 pos);
	void UpdateView();

	Vector3 GetPosition() { return position; }

	void SetEdges(Vector2 min, Vector2 max)
	{
		this->minEdge = min;
		this->maxEdge = max;
		bEdge = true;
	}

	void SetEdges(bool bEdge) { this->bEdge = bEdge; }

private:
	Camera();
	~Camera();

	ViewProjectionBuffer* VPBuffer = nullptr;
	Matrix view, proj;

	Vector3 position = Vector3(0, 0, 0);

	Vector2 minEdge = Vector2(0, 0);
	Vector2 maxEdge = Vector2(0, 0);
	bool bEdge = false;
};