//
// Created by tonik on 08-May-22.
//

#pragma once


#include "COperation.h"

class CMultiply : COperation {
public:
    CMultiply(std::shared_ptr<CMatrix> lhs, std::shared_ptr<CMatrix> rhs): COperation(std::move(lhs), std::move(rhs)){}

    std::shared_ptr<CMatrix> compute() override;
};




