#include "stdafx.h"
#include "TileSet.h"

TileSet::TileSet()
{
	tileSprite = new Texture2D(L"_Textures/tiles.jpg");
	
	texID = tileSprite->GetSRV();
	imageSize = Vector2((float)tileSprite->GetWidth(), (float)tileSprite->GetHeight());

	tileXCount = 10;
	tileYCount = 18;

	texelTileSize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);
}

TileSet::~TileSet()
{
	SAFE_DELETE(tileSprite);
}

void TileSet::GUI()
{
	static bool bOpen = true;
	ImGui::Begin("TileSprite", &bOpen);
	{
		int idx = 0;
		for (UINT y = 0; y < tileYCount; y++)
		{
			for (UINT x = 0; x < tileXCount; x++)
			{
				ImGui::PushID(++idx);

				if (ImGui::ImageButton(texID, ImVec2(40, 40), ImVec2(x * texelTileSize.x, y * texelTileSize.y), 
					ImVec2(texelTileSize.x + (x * texelTileSize.x), texelTileSize.y + ( y * texelTileSize.y))))
				{
					selectedStartUV = Vector2(x * texelTileSize.x, y * texelTileSize.y);
				}

				ImGui::PopID();

				if (idx % 4 != 0) 
				{
					ImGui::SameLine();
				}
			}
		}
	}
	ImGui::End();
}
