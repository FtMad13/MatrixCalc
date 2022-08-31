//
// Created by tonik on 08-May-22.
//

#include "CMultiply.h"


std::shared_ptr<CMatrix> CMultiply::compute() {
    if (lhs->rows != rhs->rows || lhs->columns != rhs->columns) {
        throw std::invalid_argument("The size of the matrices is not the same!");
    }
    CSparseMatrix res;
    res.rows = lhs->rows;
    res.columns = lhs->columns;
    unsigned int counter = 0;

    for (size_t i = 0; i < lhs->rows; ++i) {
        for (size_t j = 0; j < rhs->columns; ++j) {
            for (size_t k = 0; k < lhs->columns; ++k) {
                res.mat[std::make_pair(i, j)] += lhs->on(i, k) * rhs->on(k, j);
            }
            if(res.mat[std::make_pair(i, j)] == 0) {
                res.mat.erase(std::make_pair(i, j));
            } else {
                counter++;
            }
        }
    }

    if (counter < ((res.rows * res.columns) / 2)) {
        return std::shared_ptr<CMatrix>(res.clone());
    } else {
        CDenseMatrix dense = res.toDense();
        return std::shared_ptr<CMatrix>(dense.clone());
    }
}