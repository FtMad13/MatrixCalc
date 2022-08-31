//
// Created by tonik on 03-May-22.
//

#pragma once


#include <vector>
#include <iosfwd>
#include "CMatrix.h"

class CDenseMatrix : public CMatrix {
public:
    std::vector<std::vector<float>> mat;
public:

    bool isSquare() override;

    void transpose() override;

    CMatrix *clone() override;

    void inverse() override;

    void splitBottom(unsigned int from) override;

    void splitTop(unsigned int until) override;

    float determine() override;

    void printDense() const override;

    void gem() override;

    ~CDenseMatrix() override = default;

    void mergeRight(CMatrix &rhs) override;

    void mergeBottom(CMatrix &rhs) override;

    float on(unsigned int x, unsigned int y) const override;

    void splitRight(unsigned int from) override;

    void splitLeft(unsigned int until) override;

    unsigned int rank() override;


private:
    void print(std::ostream &str) const override;


};




