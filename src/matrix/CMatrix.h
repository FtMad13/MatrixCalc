//
// Created by tonik on 03-May-22.
//

#pragma once
#include <iomanip>
#include <iostream>
#include <math.h>
#include <memory>
#include <algorithm>


class CMatrix {
public:
    /**
     * size of the matrix
     */
    unsigned int rows, columns;
    /**
     * Virtual constructor.
     */
    virtual ~CMatrix() = default;
    /**
     * Function to return if the matrix is square.
     *
     * @return true if the matrix is square, false otherwise
     */
    virtual bool isSquare() = 0;
    /**
     * Function that returns the determinant of the matrix.
     *
     * @return the determinant of the matrix
     *
     * @throw invalid argument exception if the matrix isn't square
     */
    virtual float determine() = 0;
    /**
     * Performs the gaussian elimination method on the matrix.
     */
    virtual void gem() = 0;
    /**
     * Finds the rank of the matrix.
     *
     * @return rank of the matrix
     */
    virtual unsigned int rank() = 0;
    /**
     * Prints the matrix to the given output stream.
     * @param str stream where the matrix is supposed to be printed
     */
    virtual void print(std::ostream& str) const = 0;
    /**
     * Prints the matrix in the dense format.
     */
    virtual void printDense() const = 0;
    /**
     * Clone function of the matrix.
     *
     * @return new instance with the same values as this matrix
     */
    virtual CMatrix *clone() = 0;
    /**
     * Function that finds the value on given coordinates of the matrix.
     *
     * @param x x coordinate of the searched value
     *
     * @param y y coordinate of the searched value
     *
     * @return value on the given coordinates of the matrix
     */
    virtual float on(unsigned int x, unsigned int y) const = 0;
    /**
     * Transposes this matrix.
     */
    virtual void transpose() = 0;
    /**
     * Inverses this matrix.
     *
     * @throw invalid argument exception if the matrix isn't square
     */
    virtual void inverse() = 0;
    /**
     * Cuts the left side of the matrix.
     * @param from from which point on starts the new matrix.
     */
    virtual void splitRight(unsigned int from) = 0;
    /**
     * Cuts the right side of the matrix.
     *
     * @param until until what column should the new matrix be.
     */
    virtual void splitLeft(unsigned int until) = 0;
    /**
     * Cuts the top of the matrix.
     *
     * @param from from which point on starts the new matrix.
     */
    virtual void splitBottom(unsigned int from) = 0;
    /**
     * Cuts the bottom of the matrix.
     *
     * @param until until what row should the new matrix be.
     */
    virtual void splitTop(unsigned int until) = 0;
    /**
     * Merges the given matrix on to the right of this one.
     *
     * @param rhs the matrix to be merged to the right
     */
    virtual void mergeRight(CMatrix& rhs) = 0;
    /**
     * Merges the given matrix to the bottom of this one.
     *
     * @param rhs the matrix to be merged to the bottom
     */
    virtual void mergeBottom(CMatrix& rhs) = 0;

    /**
     * Print operator.
     *
     */
    friend std::ostream& operator<<(std::ostream& str, CMatrix const& data)
    {
        data.print(str);
        return str;
    }
};




