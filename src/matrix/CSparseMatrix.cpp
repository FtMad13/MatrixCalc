//
// Created by tonik on 03-May-22.
//

#include "CSparseMatrix.h"

bool CSparseMatrix::isSquare() {
    if(rows == columns) {
        return true;
    } else {
        return false;
    }
}

float CSparseMatrix::determine() {
    CDenseMatrix tmp = toDense();
    return tmp.determine();
}

void CSparseMatrix::gem() {
    for (size_t idx = 0; idx < rows; idx++) {
        if (on(idx, idx) == 0)
            break;
        for (size_t i = idx + 1; i < rows; ++i) {
            float d = on(i,idx) / on(idx, idx);
            for (size_t j = 0; j < columns; ++j)
            {
                float tmp = (-1)*(d * on(idx,j));
                if (mat.find(std::pair<unsigned int, unsigned int>(i, j))!=mat.end())
                    mat.at(std::pair<unsigned int, unsigned int>(i, j)) += tmp;
                else if (tmp != 0)
                    mat.emplace(std::pair<unsigned int, unsigned int>(i, j), tmp);
            }
        }
    }
}


unsigned int CSparseMatrix::rank() {
    CSparseMatrix *tmp = new CSparseMatrix(*this);
    tmp->gem();
    unsigned int count = 0;
    unsigned int was = -1;
    for(auto &a : tmp->mat)
    {
        if(was == a.first.first || a.second == 0)
            continue;
        was = a.first.first;
        count++;
    }
    delete tmp;
    return count;
}

CMatrix *CSparseMatrix::clone() {
    return new CSparseMatrix(*this);
}

float CSparseMatrix::on(unsigned int x, unsigned int y) const {
    auto it = mat.find(std::make_pair(x, y));
    if(it == mat.end())
        return 0;

    return it->second;
}


void CSparseMatrix::print(std::ostream &str) const {
    str << "sparse" << std::endl;
    str << rows << " " << columns << std::endl;
    for(const auto& a : mat)
    {
        str << a.first.first << " " << a.first.second << " "<< std::fixed << std::setprecision(2) << a.second << std::endl;
    }
}

void CSparseMatrix::transpose() {
    std::map<std::pair<unsigned int, unsigned int>, float> tmp;

    for(const auto& a : mat)
    {
        tmp[std::make_pair(a.first.second, a.first.first)] = a.second;
    }
    mat = tmp;
    std::swap(rows,columns);
}

void CSparseMatrix::printDense() const {

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            std::cout << std::fixed << std::setprecision(2) << on(i,j) << " ";
        }
        std::cout << std::endl;
    }
}

void CSparseMatrix::splitRight(unsigned int from) {
    for (size_t i = 0; i < from - 1; i++) {
        for (size_t j = 0; j < rows; j++) {
            mat.erase(std::make_pair(j, i));
        }
    }
    std::map<std::pair<unsigned int, unsigned int>, float> tmp;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            float f = on(i,j);
            if(f!=0)
                tmp[{i,j-from+1}] = f;
        }
    }
    columns -= from - 1;
    mat = tmp;
}

void CSparseMatrix::splitLeft(unsigned int until) {
    for (size_t i = until; i < columns; i++) {
        for (size_t j = 0; j < rows; j++) {
            mat.erase(std::make_pair(i, j));
        }
    }
    columns = until;
}

void CSparseMatrix::splitBottom(unsigned int from) {
    for (size_t i = 0; i < from - 1; i++) {
        for (size_t j = 0; j < columns; j++) {
            mat.erase(std::make_pair(i, j));
        }
    }
    std::map<std::pair<unsigned int, unsigned int>, float> tmp;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            float f = on(i,j);
            if(f!=0)
                tmp[{i-from+1,j}] = f;
        }
    }
    rows -= from - 1;
    mat = tmp;
}

void CSparseMatrix::splitTop(unsigned int until) {
    for (size_t i = until; i < columns; i++) {
        for (size_t j = 0; j < rows; j++) {
            mat.erase(std::make_pair(i, j));
        }
    }
    rows = until;
}

void CSparseMatrix::inverse() {
    CDenseMatrix tmp = toDense();
    tmp.inverse();
    std::map<std::pair<unsigned int, unsigned int>, float> vec;

    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < rows; j++) {
            float f = tmp.on(i,j);
            if(f != 0)
            {
                vec[{i,j}] = f;
            }
        }
    }
    mat = vec;
}

CDenseMatrix CSparseMatrix::toDense() {
    CDenseMatrix res;
    res.rows = rows;
    res.columns = columns;
    std::vector<std::vector<float>> vec(rows, std::vector<float>(columns, 0));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            vec[i][j] = on(i,j);
        }
    }
    res.mat = vec;
    return res;
}

void CSparseMatrix::mergeRight(CMatrix &rhs) {
    for (size_t i = 0; i < rhs.rows; i++) {
        for (size_t j = 0; j < rhs.columns; j++) {
            float f = rhs.on(i,j);
            if(f != 0)
            {
                mat[{i,j + rhs.columns}] = f;
            }
        }
    }
    columns += rhs.columns;
}

void CSparseMatrix::mergeBottom(CMatrix &rhs) {
    for (size_t i = 0; i < rhs.rows; i++) {
        for (size_t j = 0; j < rhs.columns; j++) {
            float f = rhs.on(i,j);
            if(f != 0)
            {
                mat[{i + rhs.rows,j}] = f;
            }
        }
    }
    rows += rhs.rows;
}
