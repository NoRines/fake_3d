#include "RenderContext.h"

RenderContext::RenderContext(int width, int height):
	Bitmap(width, height)
{}

void RenderContext::drawVerticalLine(uint32_t color, int x, int ymin, int ymax)
{
	for(int y = ymin; y <= ymax; y++)
	{
		setPixelColor(color, x, y);
	}
}
