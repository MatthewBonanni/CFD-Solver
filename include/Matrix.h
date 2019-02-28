#include <vector>

class Matrix {
        std::vector<std::vector<double> > mat;
        int rows, cols;
    public:
        // Constructors
        Matrix() {};
        Matrix(int, int, double);
        Matrix(const Matrix&);

        // Setters
        Matrix& operator=(const Matrix&);
        void SetElt(int, int, double);
        void SetRow(int, std::vector<double>);
        void SetCol(int, std::vector<double>);
        void SetSub(int, int, Matrix);

        // Getters
        std::vector<int> GetSize();
        double GetElt(int, int);
        std::vector<double> GetRow(int);
        std::vector<double> GetCol(int);
        Matrix GetSub(int);

        // Operators
        Matrix T();
        Matrix& Transp();
        Matrix operator+(const Matrix&);
        Matrix& operator+=(const Matrix&);
        Matrix operator-(const Matrix&);
        Matrix& operator-=(const Matrix&);
        void PrintMatrix();
};