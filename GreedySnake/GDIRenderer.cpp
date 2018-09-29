#include <stdint.h>
#include "GDIRenderer.h"

GDIRenderer::GDIRenderer()
{
	mBackBuffer = {};
}

GDIRenderer::~GDIRenderer()
{
	if (mBackBuffer.Memory != NULL) VirtualFree(mBackBuffer.Memory, 0, MEM_RELEASE);
}

void GDIRenderer::Resize(int width, int height)
{
	// Release memory if allocated.
	if (mBackBuffer.Memory != NULL) VirtualFree(mBackBuffer.Memory, 0, MEM_RELEASE);

	int bytesPerPixel = 4;

	// Update bitmap info.
	mBackBuffer.Info.bmiHeader.biSize = sizeof(mBackBuffer.Info.bmiHeader);
	mBackBuffer.Info.bmiHeader.biWidth = width;
	mBackBuffer.Info.bmiHeader.biHeight = -height;	// Set to nagtive, so windows will treat this bitmap as top-down.
	mBackBuffer.Info.bmiHeader.biPlanes = 1;
	mBackBuffer.Info.bmiHeader.biBitCount = bytesPerPixel * 8;
	mBackBuffer.Info.bmiHeader.biCompression = BI_RGB;

	// Update buffer.
	mBackBuffer.Width = width;
	mBackBuffer.Height = height;
	mBackBuffer.Pitch = width * bytesPerPixel;

	int memorySize = (width*height)*bytesPerPixel;
	mBackBuffer.Memory = VirtualAlloc(0, memorySize, MEM_COMMIT, PAGE_READWRITE);
}

void GDIRenderer::RenderToWindow(HDC hWindowDC, int windowWidth, int windowHeight)
{
	StretchDIBits(
		hWindowDC,
		0, 0, windowWidth, windowHeight,
		0, 0, mBackBuffer.Width, mBackBuffer.Height,
		mBackBuffer.Memory,
		&mBackBuffer.Info,
		DIB_RGB_COLORS, SRCCOPY);
}

void GDIRenderer::Update(void *data)
{
	// NOTE Bitmap pixel in memory: BB GG RR AA

	int blueOffset = *((int *)data);
	int greenOffset = *((int *)data + 1);

	// TODO do whatever you want to backbuffer
	uint8_t *row = (uint8_t *)mBackBuffer.Memory;
	for (int y = 0; y < mBackBuffer.Height; y++)
	{
		uint32_t *pixel = (uint32_t *)row;
		for (int x = 0; x < mBackBuffer.Width; x++)
		{
			uint32_t blue = (x + blueOffset);
			uint32_t green = (y + greenOffset);

			*pixel++ = ((green << 8) | blue);
		}
		row += mBackBuffer.Pitch;
	}
}
