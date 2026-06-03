#pragma once
#include <vector>

struct triplet{
    int row;
    int col;
    double value;
};

// Sparse Matrix in CSC style
class Matrix{
public:
    Matrix(int m, int n): rows(m), cols(n){}

    double* getElement(int row, int col){
        ;
    }

private:
    int rows;
    int cols;
    int nnz;

    std::vector<int> rowIdx;
    std::vector<int> colPtr;
    std::vector<double> values;
};
