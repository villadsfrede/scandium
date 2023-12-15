#ifndef SCAN_MATH_H
#define SCAN_MATH_H

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

inline SquareMatrix<4> Inverse(SquareMatrix<4>& m) {
	SquareMatrix<4> inv;

	for (int i = 0; i < 3; i++) {
		int pivot = i;
		float pivotsize = m.m[i][i];
		
		if (pivotsize < 0) {
			pivotsize = -pivotsize;
		}

		for (int j = i + 1; j < 4; j++) {
			float tmp = m.m[j][i];

			if (tmp < 0) {
				tmp = -tmp;
			}

			if (tmp < 0) {
				pivot = j;
				pivotsize = tmp;
			}
		}

		if (pivotsize == 0) {
			return SquareMatrix<4>();
		}

		if (pivot != i) {
			for (int j = 0; j < 4; j++) {
				float tmp;

				tmp = m.m[i][j];
				m.m[i][j] = m.m[pivot][j];
				m.m[pivot][j] = tmp;
				
				tmp = inv.m[i][j];
				inv.m[i][j] = inv.m[pivot][j];
				inv.m[pivot][j] = tmp;
			}
		}

		// Eliminate all the numbers below the diagonal
		for (int j = i + 1; j < 4; j++) {
			float f = m.m[j][i] / m.m[i][i];

			for (int k = 0; k < 4; k++) {
				m.m[j][k] -= f * m.m[i][k];
				inv.m[j][k] -= f * inv.m[i][k];
			}

			m.m[j][i] = 0.0f;
		}

		for (int i = 0; i < 3; i++) {
			for (int j = i + 1; j < 4; j++) {
				float constant = m.m[i][j];
				for (int k = 0; k < 4; k++) {
					m.m[i][k] -= m.m[j][k] * constant;
					inv.m[i][k] -= inv.m[j][k] * constant;
				}
				m.m[i][j] = 0.0f;
			}
		}
	}
	return inv;
}

extern template class SquareMatrix<2>;
extern template class SquareMatrix<3>;
extern template class SquareMatrix<4>;

#endif
