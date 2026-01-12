#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

class Matrix {
private:
    // Número de linhas e colunas
    int rows, cols;
    // Elementos da matriz
    std::vector<std::vector<double>> data;

public:
    
    Matrix(int r, int c);
    /* 
    Método construtor da matriz.

    Args:
        (int) r: Número de linhas
        (int) c: Número de colunas

    Returns: 
        (Matrix): Matriz rxc
    */

    int getRows() const;
    /*
    Método getter que retorna o número de linhas da matriz.

    Returns:
        (int): Número de linhas
    */
    int getCols() const;
    /*
    Método getter que retorna o número de colunas da matriz.

    Returns:
        (int): Número de colunas
    */

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

    static Matrix identity(int n);
    static Matrix diagonal(const std::vector<double>& diag);

    void print() const;
};

#endif
