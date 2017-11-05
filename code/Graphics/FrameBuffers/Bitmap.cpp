#include "Bitmap.h"
#include <algorithm>

#include <iostream>

Bitmap::Bitmap(int width, int height):
	width(width), height(height),
	buffer(new uint32_t[width*height])
{
}

Bitmap::Bitmap(const Bitmap& bitmap):
	width(bitmap.width), height(bitmap.height),
	buffer(new uint32_t[bitmap.width*bitmap.height])
{
	std::copy
	(
		bitmap.buffer,
		bitmap.buffer + (width*height),
		buffer
	);
}

Bitmap& Bitmap::operator=(const Bitmap& bitmap)
{
	Bitmap temp = bitmap;
	std::swap(temp.width, width);
	std::swap(temp.height, height);
	std::swap(temp.buffer, buffer);
	return *this;
}

Bitmap::Bitmap(Bitmap&& bitmap):
	width(bitmap.width), height(bitmap.height),
	buffer(bitmap.buffer)
{
	bitmap.buffer = nullptr;
	std::cout << "Här" << std::endl;
}

Bitmap& Bitmap::operator=(Bitmap&& bitmap)
{
	std::swap(bitmap.width, width);
	std::swap(bitmap.height, height);
	std::swap(bitmap.buffer, buffer);
	std::cout << "Härhar" << std::endl;
	return *this;
}

Bitmap::~Bitmap()
{
	delete[] buffer;
}

int Bitmap::getWidth() const
{
	return width;
}

int Bitmap::getHeight() const
{
	return height;
}

void Bitmap::clear(uint32_t color)
{
	std::fill(buffer, buffer + (width*height), color);
}

const uint32_t* const Bitmap::getBufferPointer() const
{
	return buffer;
}
