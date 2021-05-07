#pragma once
#include "Vector3.h"

class Ray;

struct CastResults
{
	bool intersects;
	Vector3 normal;
	Vector3 intersection;
	double distance;
};

class Object
{
public:
	Object() = default;
	Object(Vector3 color) : m_color(color) {}
	
	virtual ~Object() = default;
	virtual CastResults Intersects(Ray& ray) const = 0;

	//virtual Vector3 GetColor() const = 0;
private:
	Vector3 m_color;
};

