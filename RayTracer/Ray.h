#pragma once
#include <iostream>


#include "Object.h"
#include "Vector3.h"

class Ray
{
public:
	Ray(const Vector3& origin, const Vector3& direction)
		: m_origin(origin), m_direction(direction)
	{}

	Vector3 GetOrigin() const { return m_origin; }
	Vector3 GetDirection() const { return m_direction; }

	Vector3 At(const double t) const
	{
		return m_direction * t + m_origin;
	}
	
	Vector3 Cast(Object& o)
	{
		auto results = o.Intersects(*this);
		if (results.intersects)
			return 0.5 * (results.normal + Vector3(1, 1, 1));
		
		auto normalized_direction = m_direction.normalize();
		auto t = 0.5 * (normalized_direction.y() + 1.0);
		return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
	}
private:
	const Vector3 m_origin;
	const Vector3 m_direction;
	
};

