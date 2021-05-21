#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>

using std::cout;
using std::endl;

template <class T>
class Matrix {
    T **mat;
    T *storage;
    int nrows, ncols;

public:
    Matrix(int nrows, int ncols) : mat(nullptr), storage(nullptr), nrows(0), ncols(0) {
        init(nrows, ncols);
    }

    Matrix(const Matrix<T> &m) : mat(nullptr), storage(nullptr), nrows(0), ncols(0) {
        *this = m;
    }

    void init(int nrows, int ncols) {
        clear();
        this->nrows = nrows;
        this->ncols = ncols;
        storage = new T[nrows * ncols];
        mat = new T*[nrows];
        for (int i = 0; i < nrows; ++i) {
            mat[i] = storage + i * ncols;
        }
    }

    Matrix<T>& operator=(const Matrix<T> &m) {
        // If dims not equal, recreate matrix
        if (nrows != m.nrows || ncols != m.ncols) {
            if (storage != nullptr) delete[] storage;
            if (mat != nullptr) delete[] mat;
            nrows = m.nrows;
            ncols = m.ncols;
            storage = new T[nrows * ncols];
            mat = new T*[nrows];
            for (int i = 0; i < nrows; ++i) {
                mat[i] = storage + i * ncols;
            }
        }
        // copy matrix
        for (int i = 0; i < nrows; ++i) {
            for (int j = 0; j < ncols; ++j) {
                (*this)[i][j] = m[i][j];
            }
        }
        return *this;
    }

    T* operator[](int i) const {
        return mat[i];
    }

    void print() {
        for (int i = 0; i < nrows; ++i) {
            for (int j = 0; j < ncols; ++j) {
                cout << (*this)[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void clear() {
        if (mat != nullptr)
            delete[] mat;
        if (storage != nullptr)
            delete[] storage;
        mat = nullptr;
        storage = nullptr;
        nrows = 0;
        ncols = 0;
    }

    ~Matrix() {
        clear();
    }
};

#endif