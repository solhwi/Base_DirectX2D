#pragma once

class TileSet
{
public:
	friend class TileMap;
	TileSet();
	~TileSet();

	void GUI();

private:
	Texture2D* tileSprite = nullptr;
	ImTextureID texID;
	Vector2 imageSize;

	UINT tileXCount, tileYCount;
	Vector2 texelTileSize;
	Vector2 selectedStartUV;
};