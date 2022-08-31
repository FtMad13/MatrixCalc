//
// Created by ftmad on 5/10/22.
//

#pragma once

#include "COperation.h"

class CSubtract  : COperation {
public:
    CSubtract(std::shared_ptr<CMatrix> lhs, std::shared_ptr<CMatrix> rhs): COperation(std::move(lhs), std::move(rhs)){}
    std::shared_ptr<CMatrix> compute() override;
};


