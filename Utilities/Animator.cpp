#include "stdafx.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D * srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReverse, bool bLoop)
	:clipName(clipName), frameCount(frameCount), bReverse(bReverse), bLoop(bLoop)
{
	srv = srcTex->GetSRV();
	
	float imageWidth = (float)srcTex->GetWidth();
	float imageHeight = (float)srcTex->GetHeight();

	Vector2 clipSize = Math::absVec2(endPos - startPos);
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	Vector2 texelSize = Vector2(1.0f / imageWidth, 1.0f / imageHeight);
	Vector2 texelStartPos = Vector2(startPos.x * texelSize.x, startPos.y * texelSize.y);
	texelFrameSize = Vector2(frameSize.x * texelSize.x, frameSize.y * texelSize.y);

	for (UINT i = 0; i < frameCount; i++)
	{
		Vector2 keyFrame;
		keyFrame.x = texelStartPos.x + texelFrameSize.x * i;
		keyFrame.y = texelStartPos.y;
		keyFrames.push_back(keyFrame);
	}
}

AnimationClip::~AnimationClip()
{
}

Animator::Animator(AnimationClip * animClip)
	: currentAnimClip(animClip)
{
	animClips.insert(make_pair(animClip->GetClipName(), animClip));
}

Animator::Animator(vector<AnimationClip*> animClips)
	: currentAnimClip(animClips[0])
{
	for (AnimationClip* clip : animClips)
	{
		this->animClips.insert(make_pair(clip->GetClipName(), clip));
	}
}

Animator::~Animator()
{
}

void Animator::Update()
{
	if (bStop) return;

	if (deltaTime > playRate)
	{
		if (currentAnimClip->GetIsReverse() == false)
		{
			currentFrameIndex++;

			if (currentFrameIndex >= currentAnimClip->GetFrameCount() && bLoop)
			{
				currentFrameIndex = 0;
			}
			else if (currentFrameIndex >= currentAnimClip->GetFrameCount() && !bLoop)
			{
				deltaTime = 0.0f;
				currentAnimClipEnded = true;
				return;
			}
			currentFrame = currentAnimClip->GetKeyFrame(currentFrameIndex);
		}
		else
		{
			currentFrameIndex--;
			if (currentFrameIndex <= 0 && bLoop)
			{
				currentFrameIndex = currentAnimClip->GetLastFrameIndex();
			}
			else if (currentFrameIndex >= currentAnimClip->GetFrameCount() && !bLoop)
			{
				deltaTime = 0.0f;
				currentAnimClipEnded = true;
				return;
			}

			currentFrame = currentAnimClip->GetKeyFrame(currentFrameIndex);
		}
		deltaTime = 0.0f;
	}
	else
	{
		deltaTime += Time::Delta();
	}
	currentAnimClipEnded = false;
}

void Animator::AddAnimClip(AnimationClip * animClip)
{
	animClips.insert(make_pair(animClip->GetClipName(), animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (clipName == currentAnimClip->GetClipName()) return;

	if (animClips.find(clipName) != animClips.end())
	{
		currentAnimClip = animClips.find(clipName)->second;
		deltaTime = 0.0f;

		if (currentAnimClip->GetIsReverse())
		{
			currentFrameIndex = currentAnimClip->GetLastFrameIndex();
		}
		else
		{
			currentFrameIndex = 0;
		}

		currentFrame = currentAnimClip->GetKeyFrame(currentFrameIndex);
	}
}
