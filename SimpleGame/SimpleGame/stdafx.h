#pragma once

#include "targetver.h"
#include "Vector.h"
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <math.h>
#define WINW 500
#define WINH 800

using namespace std;
#   define  GLUT_STROKE_ROMAN
#   define  GLUT_STROKE_MONO_ROMAN
#   define  GLUT_BITMAP_9_BY_15   
#   define  GLUT_BITMAP_8_BY_13
#   define  GLUT_BITMAP_TIMES_ROMAN_10
#   define  GLUT_BITMAP_TIMES_ROMAN_24
#   define  GLUT_BITMAP_HELVETICA_10
#   define  GLUT_BITMAP_HELVETICA_12
#   define  GLUT_BITMAP_HELVETICA_18

struct OOBB {
	float Left;
	float Up;
	float Right;
	float Down;
};

enum {
	CHARACTER,
	BUILDING,
	BULLET,
	ARROW,
	WALL,
	BACK,
};

enum PlayerType {
	Ground,
	Flying,
};

