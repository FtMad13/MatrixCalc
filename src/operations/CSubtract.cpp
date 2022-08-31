//
// Created by ftmad on 5/10/22.
//

#include "CSubtract.h"

std::shared_ptr<CMatrix> CSubtract::compute() {
    if(lhs->rows != rhs->rows || lhs->columns != rhs->columns)
    {
        throw std::invalid_argument("The size of the matrices is not the same!");
    }
    CSparseMatrix res;
    unsigned int counter = 0;
    res.rows = lhs->rows;
    res.columns = lhs->columns;
    for(size_t i = 0; i < lhs->rows; i++) {
        for (size_t j = 0; j < lhs->rows; j++) {
            float f = lhs->on(i, j) - rhs->on(i, j);
            if(f != 0) {
                res.mat[std::make_pair(i, j)] = f;
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