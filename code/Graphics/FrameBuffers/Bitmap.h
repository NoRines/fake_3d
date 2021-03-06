#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>

class Bitmap
{
public:
	Bitmap() = delete;

	Bitmap(int width, int height);

	Bitmap(const Bitmap& bitmap);
	Bitmap& operator=(const Bitmap& bitmap);

	Bitmap(Bitmap&& bitmap);
	Bitmap& operator=(Bitmap&& bitmap);

	virtual ~Bitmap();

	int getWidth() const;
	int getHeight() const;
	int getByteWidth() const;

	void clear(uint32_t color);

	void setPixelColor(uint32_t color, int x, int y);

	const uint32_t* const getBufferPointer() const;

private:
	int width;
	int height;
	// AARRGGBB
	uint32_t* buffer;
};

#endif
