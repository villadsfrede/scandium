#ifndef SCAN_TRANSFORM_H
#define SCAN_TRANSFORM_H

#include "math.hpp"
#include "vector.hpp"

class Transform {
public:
	Transform(SquareMatrix<4> m) : m(m) {}
	Transform(float matrix[4][4]) : Transform(SquareMatrix<4>(matrix)) {}

	template <typename T>
	Point3<T> operator () (Point3<T> p);

private:
	SquareMatrix<4> m;
};

template <typename T>
Point3<T> Transform::operator()(Point3<T> p) {
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

#endif
