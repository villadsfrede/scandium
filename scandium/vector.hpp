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

template <template <class> class C, typename T>
inline C<T> Min(Tuple3<C, T> t1, Tuple3<C, T> t2) {
	using std::min;
	return { min(t1.x, t2.x), min(t1.y, t2.y), min(t1.z, t2.z) };
}

template <template <class> class C, typename T>
inline C<T> Max(Tuple3<C, T> t1, Tuple3<C, T> t2) {
	using std::max;
	return { max(t1.x, t2.x), max(t1.y, t2.y), max(t1.z, t2.z) };
}

//////////////////////////
//        VECTOR        //
//////////////////////////

template <typename T>
class Vector3 : public Tuple3<Vector3, T> {
public:
	Vector3(T x = 0, T y = 0, T z = 0) : Tuple3<Vector3, T>(x, y, z) {}
};

template <typename T>
inline T Dot(const Vector3<T>& v1, Vector3<T>& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2) {
	return { (v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x) };
}

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

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

//////////////////////////
//        NORMAL        //
//////////////////////////

template <typename T>
class Normal3 : public Tuple3<Normal3, T> {
	Normal3(T x, T y, T z) : Tuple3<Normal3, T>(x, y, z) {}
};

using Normal3f = Normal3<float>;
using Normal3i = Normal3<int>;

//////////////////////////
//        BOUNDS        //
//////////////////////////

template <typename T>
class Bounds3 {
public:
	Bounds3() {
		T minNum = std::numeric_limits<T>::lowest();
		T maxNum = std::numeric_limits<T>::max();
		pMin = Point3<T>(maxNum, maxNum, maxNum);
		pMax = Point3<T>(minNum, minNum, minNum);
	}

	Bounds3(Point3<T> p1, Point3<T> p2) : pMin(Min(p1, p2)), pMax(Max(p1, p2)) {}

	
	Point3<T> Corner(int corner) const {
		return Point3<T>;
	}

	Point3<T> pMin, pMax;
};

using Bounds3f = Bounds3<float>;
using Bounds3i = Bounds3<int>;

#endif
