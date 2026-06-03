#include <algorithm>

#include "../include/math/matrix.h"

void Matrix::build(std::vector<Entry>& entries, int dimension){
    n = dimension;

    std::sort(
        entries.begin(),
        entries.end(),
        [](const Entry& a,
           const Entry& b){
            if(a.col != b.col){
                return a.col < b.col;
            }
            return a.row < b.row;
           }
    );

    nnz = entries.size();
    rowIdx.resize(nnz, 0);
    colPtr.resize(dimension+1, 0);
    values.resize(nnz, 0.0);

    for(std::size_t i = 0; i < nnz; ++i){
        Entry& entry = entries[i];

        rowIdx[i] = entry.row;
        ++colPtr[entry.col+1];
    }

    for(int i = 1; i <= dimension; ++i){
        colPtr[i] += colPtr[i-1];
    }
}