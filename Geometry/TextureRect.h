#pragma once

class TextureRect : public Object
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring texturePath = L"");
	virtual ~TextureRect();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetSRV(wstring path);

	void SetShader(wstring shaderPath);

	void Move(Vector3 position) override;

	void Update() override;
	void Render() override;

	void GUI(int ordinal);

private:
	void TransformVertices();

	void ChangeImageFunc(const wstring& path = L"");
	void ChangeShaderFunc(const wstring& path = L"");
	void SaveTextAsFile(const string& text, const wstring& path = L"");

private:
	vector<VertexTexture> vertices;

	ID3D11ShaderResourceView* srv = nullptr;
	ID3D11ShaderResourceView* nullView = nullptr;

	wstring texturePath = L"";

	char text[255] = "";
};