#ifndef SCAN_MATH_H
#define SCAN_MATH_H

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

#endif
