#include "Matrix.h"
#include <vector>
#include <cstdio>
#include <iostream>

// Parameter constructor
Matrix::Matrix(int _rows, int _cols, double _init){
    rows = _rows;
    cols = _cols;

    mat.resize(rows);
    for (std::size_t i = 0; i != rows; ++i){
        mat[i].resize(cols, _init);
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& m_in){
    mat = m_in.mat;
    rows = m_in.rows;
    cols = m_in.cols;
}

Matrix& Matrix::operator=(const Matrix& m_in){
    if (&m_in == this){
        return *this;
    }

    rows = m_in.mat.size();
    cols = m_in.mat[0].size();

    mat.resize(rows);
    for (std::size_t i = 0; i != rows; ++i){
        mat[i].resize(cols);
    }

    mat = m_in.mat;

    return *this;
}

// Set specific element
void Matrix::SetElt(int i, int j, double val){
    mat[i][j] = val;
}

// Set specfic row
void Matrix::SetRow(int i, std::vector<double> vec){
    mat[i] = vec;
}

// Set specific column
void Matrix::SetCol(int j, std::vector<double> vec){
    for (std::size_t i = 0; i != rows; ++i){
        mat[i][j] = vec[i];
    }
}

// Set specific submatrix at given index
void Matrix::SetSub(int loc_x, int loc_y, Matrix m_in){
    int in_rows = m_in.GetSize()[0];
    int in_cols = m_in.GetSize()[1];

    for (std::size_t i = loc_x; i != loc_x+in_rows; ++i){

        for (std::size_t j = loc_y; j != loc_y+in_cols; ++j){

            mat[i][j] = m_in.GetElt(i-loc_x, j-loc_y);
        }
    }
}

// Get the size of the matrix
std::vector<int> Matrix::GetSize(){
    return {rows, cols};
}

// Get specific element from matrix
double Matrix::GetElt(int i, int j){
    return mat[i][j];
}

// Get specific row from matrix
std::vector<double> Matrix::GetRow(int i){
    return mat[i];
}

// Get specific column from matrix
std::vector<double> Matrix::GetCol(int j){
    std::vector<double> vec(rows);

    for (std::size_t i = 0; i != rows; ++i){
        vec[i] = mat[i][j];
    }

    return vec;
}

// Return transpose of matrix
Matrix Matrix::T(){
    Matrix result(rows, cols, 0);
    
    for (std::size_t i = 0; i != rows; ++i){
        for (std::size_t j = 0; j != cols; ++j){
            result.SetElt(i, j, mat[j][i]);
        }
    }

    return result;
}

// Transpose this matrix
Matrix& Matrix::Transp(){
    Matrix result(rows, cols, 0);
    
    for (std::size_t i = 0; i != rows; ++i){
        for (std::size_t j = 0; j != cols; ++j){
            result.SetElt(i, j, mat[j][i]);
        }
    }

    *this = result;
    return *this;
}

// Add two matrices
Matrix Matrix::operator+(const Matrix& m_in){
    Matrix result(rows, cols, 0);

    for (std::size_t i = 0; i != rows; ++i){
        for (std::size_t j = 0; j != cols; ++j){
            result.SetElt(i, j, mat[i][j] + m_in.mat[i][j]);
        }
    }

    return result;
}

// Add matrix to this
Matrix& Matrix::operator+=(const Matrix& m_in){
    for (std::size_t i = 0; i != rows; ++i){
        for (std::size_t j = 0; j != cols; ++j){
            mat[i][j] = mat[i][j] + m_in.mat[i][j];
        }
    }

    return *this;
}

// Subtract two matrices
Matrix Matrix::operator-(const Matrix& m_in){
    Matrix result(rows, cols, 0);

    for (std::size_t i = 0; i != rows; ++i){
        for (std::size_t j = 0; j != cols; ++j){
            result.SetElt(i, j, mat[i][j] - m_in.mat[i][j]);
        }
    }

    return result;
}

// Subtract matrix from this
Matrix& Matrix::operator-=(const Matrix& m_in){
    for (std::size_t i = 0; i != rows; ++i){
        for (std::size_t j = 0; j != cols; ++j){
            mat[i][j] = mat[i][j] - m_in.mat[i][j];
        }
    }

    return *this;
}

// Print matrix to screen
void Matrix::PrintMatrix(){
    for (std::size_t i = 0; i != rows; ++i){
        for (std::size_t j = 0; j != cols; ++j){
            printf("%10.2f", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}