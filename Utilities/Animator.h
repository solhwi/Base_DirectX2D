#pragma once


class AnimationClip
{
public:
	AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReverse = false, bool bLoop = true);
	~AnimationClip();

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	Vector2 GetKeyFrame(UINT index) { return keyFrames[index]; }
	Vector2 GetTexelFrameSize() { return texelFrameSize; }
	UINT GetFrameCount() { return frameCount; }
	UINT GetLastFrameIndex() { return keyFrames.size() - 1; }
	bool GetIsReverse() { return bReverse; }

	wstring GetClipName() { return clipName; }

private:
	wstring clipName = L"";
	vector<Vector2> keyFrames;
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;

	Vector2 texelFrameSize = Vector2(0, 0);
	bool bReverse = false;
	bool bLoop = true;
};


class Animator
{
public:
	Animator(AnimationClip* animClip);
	Animator(vector<AnimationClip*> animClips);
	~Animator();

	void Update();
	
	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentAnimClip->GetTexelFrameSize(); }

	void AddAnimClip(AnimationClip* animClip);
	void SetCurrentAnimClip(wstring clipName);

	void SetLoop(bool bLoop)
	{
		this->bLoop = bLoop;
	}
	
	bool currentAnimClipEnded = false;

private:
	unordered_map<wstring, AnimationClip*> animClips;
	AnimationClip* currentAnimClip = nullptr;

	float deltaTime = 0.0f;
	UINT currentFrameIndex = 0;
	Vector2 currentFrame = Vector2(0, 0);
	Vector2 texelFrameSize = Vector2(0, 0);

	bool bLoop = true;
	float playRate = 1.0f / 20.0f;
	bool bStop = false;
};