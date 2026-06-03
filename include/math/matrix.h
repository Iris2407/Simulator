#pragma once
#include <vector>

struct Entry{
    int row;
    int col;
};

// Sparse Matrix in CSC style
class Matrix{
public:
    Matrix() = default;
    ~Matrix() = default;

    void build(std::vector<Entry>& entries, int dimension);

    double* getElement(int row, int col);

private:
    int n=0;
    int nnz=0;

    std::vector<int> rowIdx;
    std::vector<int> colPtr;
    std::vector<double> values;
};
