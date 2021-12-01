#pragma once

class Circle : public Object
{
public:
	Circle(Vector3 position, Vector3 size, float rotation, int segments, Color color = Red);
	virtual ~Circle();

	void Update() override;
	void Render() override;
	
private:
	vector<VertexColor> vertices;;

	int segments = 0;
};