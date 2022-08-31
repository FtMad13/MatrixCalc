//
// Created by tonik on 03-May-22.
//


#include "CDenseMatrix.h"

float determ(std::vector<std::vector<float>> a, unsigned int n) {
    float det = 0;
    if (n == 1) {
        return a[0][0];
    } else if (n == 2) {
        det = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
        return det;
    } else {
        std::vector<std::vector<float>> submatrix(n, std::vector<float>(n, 0));
        for (size_t p = 0; p < n; p++) {
            size_t h = 0;
            size_t k = 0;
            for (size_t i = 1; i < n; i++) {
                for (size_t j = 0; j < n; j++) {
                    if (j == p) {
                        continue;
                    }
                    submatrix[h][k] = a[i][j];
                    k++;
                    if (k == n - 1) {
                        h++;
                        k = 0;
                    }
                }
            }
            det = det + a[0][p] * pow(-1, p) * determ(submatrix, n - 1);
        }
        return det;
    }
}

bool CDenseMatrix::isSquare() {
    if (rows == columns) {
        return true;
    } else {
        return false;
    }
}

float CDenseMatrix::determine() {
    if(!isSquare()) {
        throw std::invalid_argument("Matrix not square!");
    }
    return determ(mat, rows);
}

void CDenseMatrix::gem() {
    for (size_t idx = 0; idx < rows; idx++) {
        if (mat[idx][idx] == 0)
            break;
        for (size_t i = idx + 1; i < rows; ++i) {
            float d = mat[i][idx] / mat[idx][idx];
            for (size_t j = 0; j < mat[idx].size(); ++j)
                mat[i][j] -= d * mat[idx][j];
        }
    }
}

unsigned int CDenseMatrix::rank() {
    auto *tmp = new CDenseMatrix(*this);
    tmp->gem();
    int count = 0;
    for (auto &a : tmp->mat) {
        if (!std::all_of(a.begin(), a.end(), [](int i) { return i == 0; })) {
            count++;
        }
    }
    delete tmp;
    return count;
}

CMatrix *CDenseMatrix::clone() {
    return new CDenseMatrix(*this);
}

void CDenseMatrix::print(std::ostream &str) const {
    str << "dense" << std::endl;
    str << rows << " " << columns << std::endl;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            str << std::fixed << std::setprecision(2) << mat[i][j] << " ";
        }
        str << "\n";
    }
}

float CDenseMatrix::on(unsigned int x, unsigned int y) const {
    return mat[x][y];
}

void CDenseMatrix::transpose() {
    std::vector<std::vector<float> > trans_vec(mat[0].size(), std::vector<float>());
    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[i].size(); j++) {
            trans_vec[j].push_back(mat[i][j]);
        }
    }

    mat = trans_vec;
    std::swap(rows, columns);
}

void CDenseMatrix::printDense() const {
    print(std::cout);
}

void CDenseMatrix::splitRight(unsigned int from) {
    for (auto &a : mat) {
        for (size_t i = 0; i < from; i++) {
            a.erase(a.begin());
        }
    }
    columns -= from - 1;
}


void CDenseMatrix::splitLeft(unsigned int until) {
    for (auto &a : mat) {
        for (unsigned int i = columns; i > until; i--) {
            a.pop_back();
        }
    }
    columns = until;
}

void CDenseMatrix::splitBottom(unsigned int from) {
    std::vector<std::vector<float>> tmp;
    for (size_t i = from - 1; i < rows; i++) {
        tmp.push_back(mat[i]);
    }
    mat = tmp;
    rows -= from + 1;
}

void CDenseMatrix::splitTop(unsigned int until) {
    for (size_t i = 0; i < until; i++) {
        mat.pop_back();
    }
    rows -= until;
}

void CDenseMatrix::inverse() {
    if(!isSquare()) {
        throw std::invalid_argument("Matrix not square!");
    }

    std::vector<std::vector<float>> a(rows, std::vector<float>(2 * rows, 0));
    float f;

    //copying the matrix to the 2D vector for the operations
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < rows; j++) {
            a[i][j] = (*this).on(i, j);
        }
    }

    //Adding identity matrix to the right hand side
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = rows; j < 2 * rows; j++) {
            if (i == j - rows)
                a[i][j] = 1;
        }
    }

    //Elimination
    for (unsigned int i = 0; i < rows; i++) {
        f = a[i][i];
        for (unsigned int j = i; j < 2 * rows; j++)
            a[i][j] = a[i][j] / f;
        for (unsigned int j = 0; j < rows; j++) {
            if (i != j) {
                f = a[j][i];
                for (unsigned int k = 0; k < 2 * rows; k++)
                    a[j][k] = a[j][k] - f * a[i][k];
            }
        }
    }

    //Extracting the inverse matrix
    CDenseMatrix res(*this);
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = rows; j < 2 * rows; j++) {
            res.mat[i][j - rows] = a[i][j];
        }
    }
    *this = res;
}

void CDenseMatrix::mergeRight(CMatrix &rhs) {
    for (size_t j = 0; j < rhs.rows; j++) {
        for (size_t i = 0; i < rhs.columns; i++) {
            mat[j].push_back(rhs.on(j, i));
        }
    }
    columns += rhs.columns;
}

void CDenseMatrix::mergeBottom(CMatrix &rhs) {
    std::vector<float> tmp;
    for (size_t j = 0; j < rhs.rows; j++) {
        for (size_t i = 0; i < rhs.columns; i++) {
            tmp.push_back(rhs.on(j, i));
        }
        mat.push_back(tmp);
        tmp.clear();
    }
    rows += rhs.rows;
}


