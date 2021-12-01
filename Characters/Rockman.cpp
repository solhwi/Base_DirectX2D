#include "stdafx.h"
#include "Rockman.h"
#include "Scenes/Scene.h"
#include "Utilities/Animator.h"

Rockman::Rockman(Vector3 pos, Vector3 size, float rotation, wstring texturePath)
	: AnimationRect(pos, size, rotation, texturePath)
{
	animClips.push_back(new AnimationClip(L"RunR", texture, 10, { 0, 0 }, { (float)texture->GetWidth(), (float)texture->GetHeight() / 2 }));
	animClips.push_back(new AnimationClip(L"RunL", texture, 10, { 0, (float)texture->GetHeight() / 2 }, { (float)texture->GetWidth(), (float)texture->GetHeight() }, true));
	animator = new Animator(animClips);	
}

Rockman::~Rockman()
{
}

void Rockman::Move(Vector3 position)
{
	Super::Move(position);

	if (position.x > 0)
	{
		animator->SetCurrentAnimClip(L"RunR");
	}
	else if (position.x < 0)
	{
		animator->SetCurrentAnimClip(L"RunL");
	}
}
