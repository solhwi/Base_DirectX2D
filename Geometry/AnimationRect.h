#pragma once

class Animator;
class AnimationClip;

class AnimationRect : public Object
{
public:
	AnimationRect(Vector3 position, Vector3 size, float rotation, wstring texturePath = L"");
	virtual ~AnimationRect();

	void SetShader(wstring shaderPath);

	virtual void Move(Vector3 position) override;

	void Update() override;
	void Render() override;

	void GUI(int ordinal);

private:
	void TransformVertices();

private:
	vector<VertexTexture> vertices;

	wstring texturePath = L"";
	char text[255] = "";
	ID3D11SamplerState* SS = nullptr;

protected:
	
	Animator* animator = nullptr;
	vector<AnimationClip*> animClips;
	Texture2D* texture = nullptr;
};