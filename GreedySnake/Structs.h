#pragma once

#include <Windows.h>

struct Buffer
{
	BITMAPINFO	Info;
	void		*Memory;
	int			Width;
	int			Height;
	int			Pitch;
};
