#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "Bitmap.h"

class RenderContext : public Bitmap
{
public:
	RenderContext(int width, int height);

	RenderContext() = delete;
	RenderContext(const RenderContext& renderContext) = delete;
	RenderContext& operator=(const RenderContext& renderContext) = delete;
	RenderContext(RenderContext&& renderContext) = delete;
	RenderContext& operator=(RenderContext&& renderContext) = delete;

	void drawVerticalLine(uint32_t color, int x, int ymin, int ymax);
	void drawHorizontalLine(uint32_t color, int y, int xmin, int xmax);

	void drawLine(uint32_t color, int x0, int y0, int x1, int y1);
};

#endif
