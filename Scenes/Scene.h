#pragma once

#include "Renders/Resources/Texture2D.h"

#include "Geometry/Object.h"
#include "Geometry/Rect.h"
#include "Geometry/Line.h"
#include "Geometry/Circle.h"
#include "Geometry/TextureRect.h"
#include "Geometry/Items.h"
#include "Geometry/AnimationRect.h"
#include "Characters/Bomb.h"
#include "Characters/Rockman.h"
#include "Characters/Airplane.h"


#include "Utilities/RenderTexture.h"
#include "Systems/SoundSystem.h"
#include "Tilemap/TileMap.h"

class Scene
{
public:
	virtual ~Scene() {}

	virtual void Init() = 0;
	virtual void Destroy() = 0;

	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};