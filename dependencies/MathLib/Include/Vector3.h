#pragma once
#include <cmath>

class Vector3
{
private:
	float xPos;
	float yPos;
	float zPos;

public:
	Vector3(float x, float y, float z);
	Vector3();

	float Gety();
	float Getx();
	float Getz();
	float Magnitude();
	float Distance(Vector3 other);
	float DotProduct(Vector3 other);
	
	Vector3 Normalize();
	Vector3 CrossProduct(Vector3 other);

	Vector3 operator + (Vector3& rhs);
	Vector3 operator - (Vector3& rhs);
	Vector3 operator * (float& rhs);
	bool operator == (Vector3& rhs);
	bool operator != (Vector3& rhs);
};