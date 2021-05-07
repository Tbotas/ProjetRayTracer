#include "Object.h"

class Ray;

class Sphere : public Object
{
public:
	Sphere(Vector3 position, double radius)
		: m_position(position), m_radius(radius) {}
	
	~Sphere() override = default;
	CastResults Intersects(Ray& ray) const override;
private:
	Vector3 m_position;
	double m_radius;
};

