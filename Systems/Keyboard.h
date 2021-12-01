#pragma once

#define MAX_INPUT_KEY 256

#define VK_00 48
#define VK_01 49
#define VK_02 50
#define VK_03 51
#define VK_04 52
#define VK_05 53
#define VK_06 54
#define VK_07 55
#define VK_08 56
#define VK_09 57

#define KeyDown_Up Keyboard::Get()->Down('W')
#define KeyDown_Down Keyboard::Get()->Down('S')
#define KeyDown_Left Keyboard::Get()->Down('A')
#define KeyDown_Right Keyboard::Get()->Down('D')

#define KeyPress_Up Keyboard::Get()->Press('W')
#define KeyPress_Down Keyboard::Get()->Press('S')
#define KeyPress_Left Keyboard::Get()->Press('A')
#define KeyPress_Right Keyboard::Get()->Press('D')

class Keyboard : public Singleton<Keyboard>
{
public:
	friend class Singleton<Keyboard>;

	void Update();

	bool Down(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool Up(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool Press(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }

private:
	Keyboard();
	~Keyboard() {}

	byte keyState[MAX_INPUT_KEY];
	byte keyOldState[MAX_INPUT_KEY];
	byte keyMap[MAX_INPUT_KEY];

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};
};