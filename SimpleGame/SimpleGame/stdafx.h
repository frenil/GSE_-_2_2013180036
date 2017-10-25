#pragma once

#include "targetver.h"
#include "Vector.h"
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <math.h>
#define WINW 800
#define WINH 600

using namespace std;


struct OOBB {
	float Left;
	float Up;
	float Right;
	float Down;
};