#pragma once
#include <cmath>
class Vector
{
	
public:
	float x;
	float y;
	float z; 
	
	Vector();
	Vector(float x1, float y1, float z1) :x(x1),y(y1),z(z1){}
	~Vector();


	Vector operator+ (Vector v) {
		return Vector(x + v.x, y+v.y, z+v.z);
	}
	Vector operator* (float num) {
		return Vector(x*num, y *num, z *num);
	}
	Vector Normalize() {
		
		float size = sqrt(x*x + y*y + z*z);
		return Vector(x / size, y / size, z / size);
	}
};

