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
};

#endif
