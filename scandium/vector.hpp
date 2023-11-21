#ifndef SCAN_VECTOR_H
#define SCAN_VECTOR_H

template <template <typename> class Child, typename T>
class Tuple3 {
public:
	Tuple3(T x, T y, T z) : x(x), y(y), z(z) {}

	T operator[](int i) const {
		if (i == 0) { return x; }
		if (i == 1) { return y; }
		if (i == 2) { return z; }
	}
	
	T& operator[](int i) {
		if (i == 0) { return x; }
		if (i == 1) { return y; }
		if (i == 2) { return z; }
	}
	
	template <typename U>
	auto operator + (Child<U> c) const->Child<decltype(T{} + U{}) > {
		return { x + c.x, y + c.y, z + c.z };
	}

	template <typename U>
	Child<T>& operator += (Child<U> c) {
		x += c.x;
		y += c.y;
		z += c.z;
		return static_cast<Child<T> &>(*this);
	}

	template <typename U>
	auto operator - (Child<U> c) const->Child<decltype(T{} - U{}) > {
		return { x - c.x, y - c.y, z - c.z };
	}

	template <typename U>
	Child<T>& operator -= (Child<U> c) {
		x -= c.x;
		y -= c.y;
		z -= c.z;
		return static_cast<Child<T> &>(*this);
	}

	template <typename U>
	auto operator * (U s) const->Child<decltype(T{} * U{}) > {
		return { s * x, s * y, s * z };
	}

	template <typename U>
	Child<T>& operator *= (U s) {
		x *= s;
		y *= s;
		z *= s;
		return static_cast<Child<T> &>(*this);
	}

	template <typename U>
	auto operator / (U d) const->Child<decltype(T{} / U{}) > {
		return { x / d, y / d, z / d };
	}

	template <typename U>
	Child<T>& operator /= (U d) {
		x /= d;
		y /= d;
		z /= d;
		return static_cast<Child<T> &>(*this);
	}

	bool operator == (Child<T> c) const { return x == c.x && y == c.y && z == c.z; }
	bool operator != (Child<T> c) const { return x != c.x || y != c.y || z != c.z; }

	Child<T> operator - () const { return { -x, -y, -z }; }

	T x{}, y{}, z{};
};

// Tuple3 inline functions
template <template <class> class C, typename T>
inline C<T> Abs(Tuple3<C, T> t) {
	using std::abs;
	return { abs(t.x), abs(t.y), abs(t.z) };
}
//////////////////////////
//        VECTOR        //
//////////////////////////

template <typename T>
class Vector3 : public Tuple3<Vector3, T> {
public:
	Vector3(T x, T y, T z) : Tuple3<Vector3, T>(x, y, z) {}
};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

template <typename T>
inline T Dot(const Vector3<T>& v1, Vector3<T>& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2) {
	return { (v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x) };
}

//////////////////////////
//        POINTS        //
//////////////////////////

template <typename T>
class Point3 : public Tuple3<Point3, T> {
public:
	Point3(T x, T y, T z) : Tuple3<Point3, T>(x, y, z) {}
};

using Point3f = Point3<float>;
using Point3i = Point3<int>;

#endif
