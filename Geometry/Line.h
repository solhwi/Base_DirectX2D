#pragma once

class Line : public Object
{
public:
	Line(Vector3 position, float length, float rotation, Color color = Red);
	virtual ~Line();

	void Update() override;
	void Render() override;

private:
	vector<VertexColor> vertices;
};