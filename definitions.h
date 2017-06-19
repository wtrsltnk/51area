#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <windows.h>
#include <scrnsave.h>
#include "GraphicsEngine.h"
#include "GraphicsView.h"
#include "resource.h"


struct Area
{
	int x;
	int y;
	int width;
	int height;
	float red;
	float green;
	float blue;
	float opaque;
};

struct Setting 
{ 
    LPCSTR lpKeyName;
	LPCTSTR lpValueName; 
    DWORD dwValue; 
	DWORD dwType;
	DWORD dwSize;
};

void GenerateArea(int maxX, int maxY, Area& area);
void RenderArea(Area& area);
void GetSetting(Setting &setting);
void SetSetting(Setting &setting);

#define SPEED_FAST 0
#define SPEED_NORMAL 1
#define SPEED_SLOW 2

#endif