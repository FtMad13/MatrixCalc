//
// Created by tonik on 03-May-22.
//

#pragma once


#include <map>
#include <iomanip>
#include <fstream>
#include <memory>

#include "../matrix/CMatrix.h"
#include "../matrix/CDenseMatrix.h"
#include "../operations/CAdd.h"
#include "../operations/CMultiply.h"
#include "../operations/CSubtract.h"

class CCalculator {
    /**
     * Map which contains all the inputted matrices, their names are used as a key.
     */
    std::map<std::string, std::shared_ptr<CMatrix>> matrices;
public:
    /**
     * Runs the application, also contains the parser which processes the user inputs.
     */
    void run();
    /**
     * Loads matrix from file with given path, saves it to the matrices map with given name as key.
     *
     * @param c  name of the matrix
     *
     * @param path  path to the file containing the matrix
     *
     */
    void load(std::string c, const std::string& path);
    /**
     * Saves the matrix with given name to a file on the given path.
     *
     * @param c name of the matrix to be saved
     *
     * @param path path to the file where the matrix is to be saved
     *
     */
    void save(std::string c, const std::string& path);
};




