#ifndef SCAN_TRANSFORM_H
#define SCAN_TRANSFORM_H

#include "math.hpp"
#include "vector.hpp"
#include "ray.hpp"

class Transform {
public:
	//Transform() : m(SquareMatrix<4>()) {}
	Transform(SquareMatrix<4> m) : m(m) {}
	Transform(float matrix[4][4]) : Transform(SquareMatrix<4>(matrix)) {}

	template <typename T>
	inline Point3<T> operator () (const Point3<T> &p) const;

	template <typename T>
	inline Vector3<T> operator () (const Vector3<T> &v) const;

	inline Ray operator () (const Ray &r) const;

private:
	SquareMatrix<4> m;
};

template <typename T>
inline Point3<T> Transform::operator()(const Point3<T> &p) const {
	T xp = m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2] * p.z + m.m[0][3];
	T yp = m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2] * p.z + m.m[1][3];
	T zp = m.m[2][0] * p.x + m.m[2][1] * p.y + m.m[2][2] * p.z + m.m[2][3];
	T wp = m.m[3][0] * p.x + m.m[3][1] * p.y + m.m[3][2] * p.z + m.m[3][3];
	if (wp == 1) {
		return Point3<T>(xp, yp, zp);
	}
	else {
		return Point3<T>(xp, yp, zp) / wp;
	}
}

template <typename T>
inline Vector3<T> Transform::operator()(const Vector3<T> &v) const {
	T x = v.x, y = v.y, z = v.z;
	return Vector3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
					  m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
					  m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
}

inline Ray Transform::operator()(const Ray& r) const {
	Point3f o = (*this)(r.o);
	Vector3f d = (*this)(r.d);
	return Ray(o, d);
}

#endif
