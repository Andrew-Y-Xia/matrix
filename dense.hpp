#ifndef MATRIX_DENSE
#define MATRIX_DENSE

#include <iostream>


template<typename T, int width, int height>
class Matrix {
    private:
    T a[height][width];

    public:

    Matrix() {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                a[j][i] = 0;
            }
        }
    }

    Matrix(T* i_a) {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) { 
                a[j][i] = *i_a;
                i_a++;
            }
        }
    }

    Matrix(const Matrix<T, width, height>& other) {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                a[j][i] = other.a[j][i];
            }
        }
    }

    Matrix<T, width, height>& operator=(const Matrix<T, width, height>& other) {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                a[j][i] = other.a[j][i];
            }
        }
        return *this;
    }


    T& operator()(int y, int x) {
        return a[y][x];
    }

    Matrix<T, width, height> operator+(Matrix<T, width, height> other) {
        // Coefficient-wise add
        Matrix<T, width, height> m;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                m(j, i) = a[j][i] + other(j, i);
            }
        }
        return m;
    }

    Matrix<T, width, height> operator-(Matrix<T, width, height> other) {
        // Coefficient-wise subtract
        Matrix<T, width, height> m;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                m(j, i) = a[j][i] - other(j, i);
            }
        }
        return m;
    }

    Matrix<T, width, height> coeff_mult(Matrix<T, width, height> other) {
        // Coefficient-wise mult
        Matrix<T, width, height> m;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                m(j, i) = a[j][i] * other(j, i);
            }
        }
        return m;
    }

    template<int w2>
    Matrix<T, w2, height> operator*(Matrix<T, w2, width> other) {
        // Matrix multiplication
        Matrix<T, w2, height> m;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < w2; i++) {
                for (int k = 0; k < width; k++) {
                    m(j, i) += a[j][k] * other(k, i);
                }
            }
        }
        return m;
    }

    void apply(T func(T)) {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                a[j][i] = func(a[j][i]);
            }
        }
    }

    void print() {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                std::cout << a[j][i] << ' ';
            }
            std::cout << '\n';
        }
    }

    struct Dimensions {
        int y, x;
    };

    Dimensions get_dimensions() {
        return Dimensions{height, width};
    }
};


#endif
