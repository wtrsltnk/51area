#include "definitions.h"

void RenderArea(Area& area)
{
	::glPushMatrix();
	::glColor4f(area.red, area.green, area.blue, area.opaque);
	::glRecti(area.x, area.y, area.x + area.width, area.y + area.height);
	::glPopMatrix();
}

void GenerateArea(int maxX, int maxY, Area& area)
{
	int x = 0;
	int y = 0;
	int width = 100;
	int height = 100;
	float c[3] = {1.0f, 0.0f, 0.0f};
	
	srand(timeGetTime());
	int r = 0;

	r = rand();
	width = r % maxX;

	r = rand();
	height = r % maxY;

	r = rand();
	x = (r % maxX) - (width / 2);

	r = rand();
	y = (r % maxY) - (height / 2);

	r = rand();
	area.opaque = (float)(r % 256) / (float)256;

	r = rand();
	area.red = (float)(r % 256) / (float)256;

	r = rand();
	area.green = (float)(r % 256) / (float)256;

	r = rand();
	area.blue = (float)(r % 256) / (float)256;

	area.x = x;
	area.y = y;
	area.width = width;
	area.height = height;

}