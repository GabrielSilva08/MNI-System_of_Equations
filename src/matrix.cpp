#include "matrix.hpp"

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(r, std::vector<double>(c, 0.0));
}

int Matrix::getRows() const { 
    return rows; 
}

int Matrix::getCols() const { 
    return cols; 
}

double& Matrix::operator()(int i, int j){
    return data[i][j];
}

double Matrix::operator()(int i, int j) const {
    return data[i][j];
}

Matrix Matrix::identity(int n) {
    Matrix I(n, n);
    for (int i = 0; i < n; i++)
        I(i, i) = 1.0;
    return I;
}

Matrix Matrix::diagonal(const std::vector<double>& diag) {
    int n = diag.size();
    Matrix D(n, n);
    for (int i = 0; i < n; i++)
        D(i, i) = diag[i];
    return D;
}

void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << data[i][j] << "\t";
        std::cout << std::endl;
    }
}
