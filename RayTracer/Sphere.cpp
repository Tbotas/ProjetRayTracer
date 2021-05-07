#include "Sphere.h"

#include "Ray.h"

CastResults Sphere::Intersects(Ray& ray) const
{
	// This is an optimization to avoid hard computation
	// if it's clear the ray won't intersect with the sphere.
	
	CastResults results;
	results.intersects = false;
	
	// From https://en.wikipedia.org/wiki/Line-sphere_intersection
	// Knowing if a line and a sphere intersects is solving a quadratic equation.

	Vector3 translated_origin = ray.GetOrigin() - this->m_position;

	/*
	Vector3 L = -translated_origin;
	double tca = L.dot(ray.GetDirection());
	double d2 = L.square() - tca * tca;

	if (d2 > (this->m_radius * this->m_radius)) return results;
	*/

	
	const double a = ray.GetDirection().square();
	const double b = 2.0 * translated_origin.dot(ray.GetDirection());
	const double c = translated_origin.square() - std::pow(this->m_radius, 2);
	
	const double delta = std::pow(b, 2) - 4.0 * a * c;
	
	// A quadratic equation can have 0, 1 or 2 solutions.
	// The number of solutions depends on the discriminant (delta),
	// if it's zero or more, the equation has at least one solution.
	
	results.intersects = delta >= 0;


	// When we know solutions exist, we can easily compute them.
	// The solutions are the distances of the intersections points from the screen.
	// When we have two solutions, we want to check the lowest first,
	// because we want to point closest to the camera.
	
	auto solution = (-b - sqrt(delta)) / (2.0 * a);


	// If the solution is lower than 0, it means it's behind our camera
	// we then want to use the second solution, which would be further away
	// in the direction of our sight.
	
	if (solution < 0)
	{
		solution = (-b + sqrt(delta)) / (2.0 * a);
		
		// If the solution is still 0, then we don't have an intersection
		// in front of us, so we can't see the sphere since it's
		// completely behind our camera.
		if (solution < 0)
		{
			results.intersects = false;
			return results;
		}
	}
		
	if (results.intersects)
	{
		
		results.distance = solution;

		// Now that we have a solution, we can find the intersection
		// by plugging the solution into the ray equation.

		results.intersection = ray.At(results.distance);

		// The normal of a sphere can be found by subtracting
		// the center of the sphere from the impact point.
		// We will normalize the normal in our code.

		auto normal = (results.intersection - this->m_position) / m_radius;
		auto face = ray.GetDirection().dot(normal) < 0;
		
		results.normal = face ? normal : normal * -1;
	}
	
	return results;
}


