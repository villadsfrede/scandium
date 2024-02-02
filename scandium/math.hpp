#ifndef SCAN_MATH_H
#define SCAN_MATH_H

// Funktion til løsning af andengradsligninger
inline bool Quadratic(float a, float b, float c, float* t1, float* t2) {
	double d = (double)b * (double)b - 4 * (double)a * (double)c;
	if (d < 0) return false;
	double sqrtd = std::sqrt(d);

	*t1 = (-b - sqrtd) / (2 * a);
	*t2 = (-b + sqrtd) / (2 * a);
	if (*t1 > *t2) {
		std::swap(*t1, *t2);
	}
	return true;
}

// En kvadratisk matrix
template <int N>
class SquareMatrix {
public:
	SquareMatrix() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				m[i][j] = (i == j) ? 1 : 0;
			}
		}
	}

	SquareMatrix(float matrix[N][N]) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				m[i][j] = matrix[i][j];
			}
		}
	}

	float m[N][N];
};

extern template class SquareMatrix<4>;

// Funktion til at klemme værdi mellem maksimum og minimum
inline float Clamp(float lo, float hi, float x) {
	if (x < lo) { return lo; }
	if (x > hi) { return hi; }
	return x;
}

#endif
