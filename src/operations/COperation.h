//
// Created by tonik on 08-May-22.
//

#pragma once


#include "../matrix/CMatrix.h"
#include "../matrix/CSparseMatrix.h"
#include <memory>

class COperation {
public:
    std::shared_ptr<CMatrix> lhs, rhs;
    /**
     * Constructor
     *
     * @param a right hand side matrix
     *
     * @param b left hand side matrix
     *
     */
    COperation (std::shared_ptr<CMatrix> a, std::shared_ptr<CMatrix> b) : lhs(a), rhs(b)  {}
    /**
     * Performs the operation on the matrices.
     *
     * @return shared pointer to the result of the operation
     *
     * @throw invalid argument exception if the parameters of the given matrices aren't compatible with the operation
     */
    virtual std::shared_ptr<CMatrix> compute() = 0;
};




