#pragma once

class Gui : public Singleton<Gui>
{
public:
	friend class Singleton<Gui>;

	LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void PrintFrame();
	void TextureRectGUIS(vector<class TextureRect*>& trVec, const char* name);

	void Update();
	void Render();

private:
	Gui();
	~Gui();

private:
	void ApplyStyle();
};