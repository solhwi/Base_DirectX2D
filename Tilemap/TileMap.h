#pragma once

struct Tile
{
	Vector3 pos;
	Vector2 uvStart;
	Vector2 uvEnd;

	Color color;
};

class TileMap : public Object
{
public:
	TileMap(Vector3 pos, Vector3 size, float r, UINT spacing);
	~TileMap();
	
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderPath);
	
	void Update() override;
	void Render() override;

	void GUI();

private:
	void GenerateTileMap(UINT width, UINT height, UINT spacing);
	Tile* GetTile(Vector3 worldMousePos);

	void SaveTileMap(const wstring& path = L"");
	void LoadTileMap(const wstring& path = L"");

private:
	UINT spacing;
	UINT width, height;
	UINT vertexCount;
	UINT indexCount;

	vector<VertexTextureColor> vertices;
	Tile** tiles;

	ID3D11ShaderResourceView* srv = nullptr;
	ID3D11RasterizerState* rs = nullptr;
	ID3D11RasterizerState* rs2 = nullptr;

	class TileSet* tileSet;
};