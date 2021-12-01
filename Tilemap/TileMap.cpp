#include "stdafx.h"
#include "TileMap.h"
#include "TileSet.h"

TileMap::TileMap(Vector3 pos, Vector3 size, float r, UINT spacing)
	: Object(pos, size, r, L"_Shaders/VertexTile.hlsl"), spacing(spacing)
{
	tileSet = new TileSet();

	spacing = 40; // ÇÑÄ­ Å©±â
	width = size.x / spacing;
	height = size.y / spacing;

	GenerateTileMap(width, height, spacing);

	vertices.assign(4, VertexTextureColor());

	vertices[0].position = Vector3(0, 0, 0);
	vertices[0].uv = Vector2(0, 1);

	vertices[1].position = Vector3(0, (float)spacing, 0);
	vertices[1].uv = Vector2(0, 0);

	vertices[2].position = Vector3((float)spacing, 0, 0);
	vertices[2].uv = Vector2(1, 1);

	vertices[3].position = Vector3((float)spacing, (float)spacing, 0);
	vertices[3].uv = Vector2(1, 0);

	vertices[0].color = Red;
	vertices[1].color = Red;
	vertices[2].color = Red;
	vertices[3].color = Red;

	indices = { 0,1,2,2,1,3 };

	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexTextureColor::descs, VertexTextureColor::count, VS->GetBlob());
	
	srv = tileSet->tileSprite->GetSRV();
}

TileMap::~TileMap()
{
	SAFE_DELETE_ARRAY(tiles);
	SAFE_DELETE(tileSet);

	SAFE_RELEASE(rs);
	SAFE_RELEASE(rs2);

	SAFE_RELEASE(srv);
}

void TileMap::SetShader(wstring shaderPath)
{
	if (VS)
	{
		VS->Clear();
		VS->Create(shaderPath, "VS");
	}

	if (PS)
	{
		PS->Clear();
		PS->Create(shaderPath, "PS");
	}
}

void TileMap::Update()
{
	Super::Update();

	if (Mouse::Get()->Press(0))
	{
		Vector3 mPos = Mouse::Get()->GetPosition();
		Tile* tile = GetTile(mPos);

		if (tile)
		{
			tile->uvStart = tileSet->selectedStartUV;
			tile->uvEnd = tileSet->selectedStartUV + tileSet->texelTileSize;
		}
	}
}

void TileMap::Render()
{
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	VS->SetShader();
	PS->SetShader();

	if (srv)
	{
		DC->PSSetShaderResources(0, 1, &srv);
	}

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			Tile& tile = tiles[y][x];
			{
				D3D11_MAPPED_SUBRESOURCE subResource;

				DC->Map(VB->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
				vertices[0].uv = Vector2(tile.uvStart.x, tile.uvEnd.y);
				vertices[1].uv = tile.uvStart;
				vertices[2].uv = tile.uvEnd;
				vertices[3].uv = Vector2(tile.uvEnd.x, tile.uvStart.y);

				memcpy(subResource.pData, vertices.data(), sizeof(VertexTextureColor) * vertices.size());
				DC->Unmap(VB->GetResource(), 0);
			}

			D3DXMatrixTranslation(&world, tile.pos.x + position.x, tile.pos.y + position.y, 0);

			WB->SetWorld(world);
			WB->SetVSBuffer(0);

			DC->DrawIndexed(IB->GetCount(), 0, 0);
		}
	}
}

void TileMap::GUI()
{
	tileSet->GUI();

	static bool bOpen = true;

	if (ImGui::Begin("TileMap", &bOpen))
	{
		if (ImGui::Button("Save", ImVec2(50, 30)))
		{
			SaveTileMap();
		}
		if (ImGui::Button("Load", ImVec2(50, 30)))
		{
			LoadTileMap();
		}
	}
	ImGui::End();
}

void TileMap::GenerateTileMap(UINT width, UINT height, UINT spacing)
{
	if (width == 0 || height == 0 || spacing == 0)
	{
		Assert(false);
		return;
	}

	tiles = new Tile*[height];
	
	for (UINT y = 0; y < height; y++)
	{
		tiles[y] = new Tile[width];

		for (UINT x = 0; x < width; x++)
		{
			tiles[y][x].pos.x = (float)(x * spacing);
			tiles[y][x].pos.y = (float)(y * spacing);
			tiles[y][x].pos.z = 0;

			tiles[y][x].color = Color(0, 0, 0, 1);
			tiles[y][x].uvStart = Vector2(0, 0);
			tiles[y][x].uvEnd = Vector2(0, 0);
		}
	}


}

Tile * TileMap::GetTile(Vector3 worldMousePos)
{
	UINT x = ((int)worldMousePos.x + (int)Camera::Get()->GetPosition().x) / spacing;
	UINT y = ((int)worldMousePos.y + (int)Camera::Get()->GetPosition().y) / spacing;
	
	if (x >= width || y >= height || x < 0 || y < 0)
	{
		return nullptr;
	}

	return &tiles[y][x];
}

void TileMap::SaveTileMap(const wstring & path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TileMap::SaveTileMap, this, placeholders::_1);
		Path::SaveFileDialog(L"", Path::TileMapFilter, L"", func, handle);
	}
	else
	{
		if (!tiles) return;

		FileStream* out = new FileStream(String::ToString(path), FILE_STREAM_WRITE);
		out->Write(width);
		out->Write(height);


		for (UINT y = 0; y < height; y++)
		{
			for (UINT x = 0; x < width; x++)
			{
				out->Write(tiles[y][x]);
			}
		}

		SAFE_DELETE(out);
	}
}

void TileMap::LoadTileMap(const wstring & path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TileMap::LoadTileMap, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::TileMapFilter, L"", func, handle);
	}
	else
	{
		if (!tiles) return;

		FileStream* in = new FileStream(String::ToString(path), FILE_STREAM_READ);
		width = in->Read<UINT>();
		height = in->Read<UINT>();

		for (UINT y = 0; y < height; y++)
		{
			for (UINT x = 0; x < width; x++)
			{
				tiles[y][x] = in->Read<Tile>();
			}
		}

		SAFE_DELETE(in);
	}
}
