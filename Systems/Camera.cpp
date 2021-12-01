#include "stdafx.h"
#include "Camera.h"

void Camera::Update()
{
	if (Keyboard::Get()->Press(VK_LSHIFT) && KeyPress_Up)
	{
		position.y += 100 * Time::Delta();
	}
	else if (Keyboard::Get()->Press(VK_LSHIFT) && KeyPress_Down)
	{
		position.y -= 100 * Time::Delta();
	}

	if (Keyboard::Get()->Press(VK_LSHIFT) && KeyPress_Right)
	{
		position.x += 100 * Time::Delta();
	}
	else if (Keyboard::Get()->Press(VK_LSHIFT) && KeyPress_Left)
	{
		position.x -= 100 * Time::Delta();
	}

	Move(position);
}

void Camera::Render()
{
	VPBuffer->SetVSBuffer(1);
}

void Camera::Move(Vector3 pos)
{
	if (bEdge)
	{
		if (pos.x < minEdge.x)
		{
			pos.x = minEdge.x;
		}
		else if (pos.x + WinMaxWidth > maxEdge.x)
		{
			pos.x = maxEdge.x - WinMaxWidth;
		}

		if (pos.y < minEdge.y)
		{
			pos.y = minEdge.y;
		}
		else if (pos.y + WinMaxHeight > maxEdge.y)
		{
			pos.y = maxEdge.y - WinMaxHeight;
		}
	}
	this->position = pos;
	UpdateView();
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH(&view, &position, &(position + Vector3(0, 0, 1)), &Vector3(0, 1, 0));
	VPBuffer->SetView(view);
}

Camera::Camera()
{
	VPBuffer = new ViewProjectionBuffer();

	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&proj);

	//D3DXMatrixOrthoLH(&projection, WinMaxWidth, WinMaxHeight, 0, 1);
	D3DXMatrixOrthoOffCenterLH(&proj, 0, WinMaxWidth, 0, WinMaxHeight, 0, 1);

	VPBuffer->SetProjection(proj);
}

Camera::~Camera()
{
	SAFE_DELETE(VPBuffer);
}
