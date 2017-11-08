#include "RenderContext.h"
#include <cmath>
#include <algorithm>

RenderContext::RenderContext(int width, int height):
	Bitmap(width, height)
{}

void RenderContext::drawVerticalLine(uint32_t color, int x, int ymin, int ymax)
{
	for(int y = ymin; y < ymax; y++)
	{
		setPixelColor(color, x, y);
	}
}

void RenderContext::drawLine(uint32_t color, int x0, int y0, int x1, int y1)
{
	bool x_axis = true;
	if(abs(x1 - x0) < abs(y1 - y0))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		x_axis = false;
	}
	
	if(x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	else if(x0 == x1)
	{
		return;
	}
	const int slope = ((y1 - y0) << 16) / (x1 - x0);
	const int offset = y0 - ((x0*slope) >> 16);
	for(int x = x0; x < x1; x++)
	{
		if(x_axis)
		{
			setPixelColor(color, x, ((x*slope) >> 16) + offset);
		}
		else
		{
			setPixelColor(color, ((x*slope) >> 16) + offset, x);
		}
	}
}
