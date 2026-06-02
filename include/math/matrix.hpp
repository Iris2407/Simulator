#pragma once
#include <vector>

class Solver;

class Matrix{
public:
    Matrix(int d): dimension(d){}
    virtual ~Matrix() = default;

    virtual void add(int row, int col, double value) = 0;
    virtual void clear() = 0;

    friend class Solver;

private:
    int dimension;
};

class DenseMatrix: public Matrix{
public:
    DenseMatrix(int d): Matrix(d){}
    private:
    std::vector<std::vector<double>> data;
};

class SparseMatrix: public Matrix{
    public:
    private:
};
