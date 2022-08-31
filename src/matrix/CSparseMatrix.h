//
// Created by tonik on 03-May-22.
//

#pragma once


#include "CMatrix.h"
#include "CDenseMatrix.h"
#include <map>

class CSparseMatrix : public CMatrix {
public:
    /**
     * Map which stores the values and their coordinates.
     */
    std::map<std::pair<unsigned int, unsigned int>, float> mat;

    void transpose() override;

    void printDense() const override;

    bool isSquare() override;

    float determine() override;

    void gem() override;

    CMatrix *clone() override;

    unsigned int rank() override;

    void mergeRight(CMatrix &rhs) override;

    void mergeBottom(CMatrix &rhs) override;

    void inverse() override;

    void splitBottom(unsigned int from) override;

    void splitTop(unsigned int until) override;

    void splitRight(unsigned int from) override;

    void splitLeft(unsigned int until) override;

    float on(unsigned int x, unsigned int y) const override;

    void print(std::ostream &str) const override;

    ~CSparseMatrix() override = default;
    /**
     * Function that converts this matrix to the dense format.
     *
     * @return dense matrix of the same values.
     */
    CDenseMatrix toDense();
};





