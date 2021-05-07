#pragma once
#include <cmath>
#include <ostream>


class Vector3
{
public:
	Vector3() : m_vector3{ 0, 0, 0 } {}
	Vector3(double x, double y, double z) : m_vector3{x, y, z} {}
	~Vector3() = default;
	
	double x() const { return m_vector3[0]; }
	double y() const { return m_vector3[1]; }
	double z() const { return m_vector3[2]; }

	Vector3 operator-() const { return Vector3(-m_vector3[0], -m_vector3[1], -m_vector3[2]); }
	
	double square() const
	{
		return x() * x() + y() * y() + z() * z();
	}
	
	double length() const
	{
		return std::sqrt(this->square());
	}

	Vector3 normalize() const
	{
		auto l = length();
		return Vector3(x() / l, y() / l, z() / l); 
	}

	double dot(const Vector3& other) {
		return x() * other.x()
			+ y() * other.y()
			+ z() * other.z();
	}

	Vector3 cross(const Vector3& other) {
		return Vector3(this->y() * other.z() - this->z() * other.y(),
				this->z() * other.x() - this->x() * other.z(),
				this->x() * other.y() - this->y() * other.x());
	}
private:
	double m_vector3[3];
};

inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
	return out << "Vector3(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
}

inline Vector3 operator+(const Vector3& a, const Vector3& b) {
	return Vector3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}

inline Vector3 operator-(const Vector3& a, const Vector3& b) {
	return Vector3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

inline Vector3 operator*(const Vector3& a, const Vector3& b) {
	return Vector3(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
}

inline Vector3 operator*(const double a, const Vector3& b) {
	return Vector3(a * b.x(), a * b.y(), a * b.z());
}

inline Vector3 operator*(const Vector3& a, double b) {
	return b * a;
}

inline Vector3 operator/(const Vector3 a, double b) {
	return (1 / b) * a;
}