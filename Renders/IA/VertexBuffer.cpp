#include "stdafx.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
