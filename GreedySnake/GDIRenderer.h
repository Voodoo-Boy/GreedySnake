#pragma once

#include "Structs.h"

class GDIRenderer
{
public:
	GDIRenderer();
	~GDIRenderer();

	void Resize(int width, int height);
	void Update(void *data);
	void RenderToWindow(HDC hWindowDC, int windowWidth, int windowHeight);

private:
	Buffer mBackBuffer;
};
