//
// Created by tonik on 03-May-22.
//

#include <iostream>
#include "CCalculator.h"


void CCalculator::run() {
    std::string input;
    std::cout << "Matrix Calculator v0.1, type !help for available commands" << std::endl;

    while (true) {
        std::cin >> input;
        std::string name;
        if (input == "exit") {
            break;
        } else if (input == "new") {
            std::string type;
            size_t rows, columns;
            std::cout << "enter type: " << std::endl;
            std::cin >> type;
            std::cout << "enter name: " << std::endl;
            std::cin >> name;
            std::cout << "enter rows, columns: " << std::endl;
            std::cin >> rows >> columns;
            if(type == "dense") {
                CDenseMatrix dense;
                dense.rows = rows;
                dense.columns = columns;
                std::vector<std::vector<float>> vec(rows, std::vector<float>(columns, 0));
                for (size_t i = 0; i < rows; i++) {
                    for (size_t j = 0; j < columns; j++) {
                        std::cout << "Enter [" << i << "][" << j << "]: " << std::flush;
                        std::cin >> vec[i][j];
                    }
                }
                dense.mat = vec;
                matrices[name] = std::shared_ptr<CMatrix>(dense.clone());
            } else if (type == "sparse") {
                CSparseMatrix sparse;
                sparse.rows = rows;
                sparse.columns = columns;
                std::cout << "Enter triplets (row column value), enter 0 0 0 when done" << std::endl;
                size_t x, y;
                float f;
                while(true) {
                    std::cin >> x >> y >> f;
                    if(f == 0 && x == 0 && y == 0) {
                        std::cout << "matrix created!" << std::endl;
                        break;
                    }
                    if(f!=0)
                        sparse.mat[{x,y}] = f;
                }
                matrices[name] = std::shared_ptr<CMatrix>(sparse.clone());
            } else {
                throw std::invalid_argument("no such format");
            }
        } else if (input == "load") {
            std::string path;
            std::cin >> name >> path;
            load(name, path);
        } else if (input == "save") {
            std::string path;
            std::cin >> name >> path;
            if (!matrices.count(name)) {
                std::cout << "No matrix with this name!" << std::endl;
                continue;
            }
            save(name, path);
        } else if (input == "print") {
            std::cin >> name;
            if (!matrices.count(name)) {
                std::cout << "No matrix with this name!" << std::endl;
                continue;
            }
            std::cout << *matrices[name];
        } else if (input == "det") {
            std::cin >> name;
            std::cout << matrices[name]->determine() << std::endl;
        } else if (input == "inv") {
            std::cout << "inverse" << std::endl;
            std::cin >> name;
            if (!matrices.count(name)) {
                std::cout << "No matrix with this name!" << std::endl;
                continue;
            }
            matrices[name]->inverse();

        } else if (input == "printd") {
            std::cin >> name;
            matrices[name]->printDense();
        } else if (input == "trans") {
            std::cin >> name;
            if (!matrices.count(name)) {
                std::cout << "No matrix with this name!" << std::endl;
                continue;
            }
            matrices[name]->transpose();
        } else if (input == "split") {
            std::string sw;
            unsigned int p;
            std::cin >> sw >> name >> p;
            if(sw == "-l")
            {
                matrices[name]->splitLeft(p);
            } else if (sw == "-r") {
                matrices[name]->splitRight(p);
            } else if (sw == "-t") {
                matrices[name]->splitTop(p);
            } else if (sw == "-b") {
                matrices[name]->splitBottom(p);
            }
        } else if (input == "merge") {
            std::string sw, name1, name2;
            std::cin >> sw >> name1 >> name2;
            if(sw == "-b")
            {
                matrices[name1]->mergeBottom(*matrices[name2]);
            } else if (sw == "-r") {
                matrices[name1]->mergeRight(*matrices[name2]);
            }
        } else if (input == "gem") {
            std::cin >> name;
            if (!matrices.count(name)) {
                std::cout << "No matrix with this name!" << std::endl;
                continue;
            }
            matrices[name]->gem();
        } else if (input == "!help") {
            std::cout << "load $matrix_name $path_to_matrix - loads matrix from file\n"
                         "save $matrix_name $path_to_save_file - saves matrix to file\n"
                         "print $matrix_name - prints matrix\n"
                         "det $matrix_name - prints determinant of given matrix\n"
                         "gem $matrix_name - performs Gaussian Elimination Method on given matrix\n"
                         "inv $matrix_name - performs inversion on given matrix\n"
                         "trans $matrix_name - transposes given matrix\n"
                         "split:\n"
                         "\tsplit -r $matrix_name $from - cuts the left side of the matrix off\n"
                         "\tsplit -l $matrix_name $until - cuts the right side of the matrix off\n"
                         "\tsplit -b $matrix_name $from - cuts the top of the matrix off\n"
                         "\tsplit -b $matrix_name $until - cuts the bottom of the matrix off\n"
                         "merge:\n"
                         "\tmerge -r $matrix1 $matrix2 - merges matrix 2 onto the right side of matrix one"
                         "\tmerge -b $matrix1 $matrix2 - merges matrix 2 onto the bottom of matrix one"
                         "operations:\n"
                         "\tmultiply: $result_matrix = $matrix1 * $matrix2\n"
                         "\tmultiply: $result_matrix = $matrix1 * $matrix2\n"
                         "\tmultiply: $result_matrix = $matrix1 * $matrix2"
                         << std::endl;
        } else {
            std::string equals, lhs, op, rhs;
            name = input;
            std::cin >> equals >> lhs >> op >> rhs;
            if (matrices.count(lhs) == 0 || matrices.count(rhs) == 0 || equals != "=" ||
                (op != "+" && op != "*" && op != "-")) {

                std::cout << "Invalid input! " << name << " " << equals << " " << lhs << op << rhs << std::endl;

            } else if (op == "+") {
                matrices[name] = CAdd(matrices[lhs], matrices[rhs]).compute();
            } else if (op == "*") {
                matrices[name] = CMultiply(matrices[lhs], matrices[rhs]).compute();
            } else if (op == "-") {
                matrices[name] = CSubtract(matrices[lhs], matrices[rhs]).compute();
            }
        }
    }
}

void CCalculator::load(std::string c, const std::string &path) {


    unsigned int m, n;
    std::string condition;

    std::ifstream f(path);
    if (!f.good()) {
        std::cout << "File not found!" << std::endl;
        return;
    }
    f >> condition;
    if (condition == "dense") {
        CDenseMatrix mat;
        f >> m >> n;
        std::vector<std::vector<float>> vec(m, std::vector<float>(n, 0));


        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                f >> vec[i][j];
            }
        }

        mat.rows = m;
        mat.columns = n;
        mat.mat = vec;


        matrices[c] = std::shared_ptr<CMatrix>(mat.clone());

    } else if (condition == "sparse") {
        CSparseMatrix mat;
        f >> m >> n;
        std::map<std::pair<unsigned int, unsigned int>, float> mymap;
        unsigned int x, y;
        float val;

        while (true) {
            f >> x >> y;
            f >> val;
            if (f.eof()) break;
            mymap[std::make_pair(x, y)] = val;
        }

        mat.rows = m;
        mat.columns = n;
        mat.mat = mymap;

        matrices[c] = std::shared_ptr<CMatrix>(mat.clone());
    } else {
        throw std::invalid_argument("Incorrect file format!");
    }
}

void CCalculator::save(std::string c, const std::string &path) {
    std::ofstream f(path);
    std::cout << matrices[c]->determine() << std::endl;
    //matrices[c]->gem();
    std::cout << std::endl;
    std::cout << "rank: " << matrices[c]->rank() << std::endl;
    std::cout << std::endl;

    if (!f.good()) {
        std::cout << "Unable to create file!" << std::endl;
        return;
    }
    f << *matrices[c];
}

