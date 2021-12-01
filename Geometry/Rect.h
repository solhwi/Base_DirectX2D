#pragma once

class Rect : public Object
{
public:
	Rect(Vector3 position, Vector3 size, float rotation, Color color = Red);
	virtual ~Rect();

	void Move(Vector3 position) override;

	void Update() override;
	void Render() override;

private:
	void TransformVertices();

private:
	vector<VertexColor> vertices;
};