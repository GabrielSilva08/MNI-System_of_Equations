#ifndef LINEAR_SYSTEM_SOLVER_HPP
#define LINEAR_SYSTEM_SOLVER_HPP

#include "matrix.hpp"
#include <vector>

// ========== Substituições ==========
std::vector<double> forwardSubstitution(const Matrix& L, const std::vector<double>& b);
/*
Realiza a substituição direta (de cima pra baixo) -> Ly = b

Args:
    (const Matrix&) L: Matriz triangular inferior com diagonal unitária;
    (const std::vector<double>&) b: Vetor.

Returns:
    (std::vector<double>): Vetor solução y
*/

std::vector<double> backwardSubstitution(const Matrix& U, const std::vector<double>& y);
/*
Realiza a substituição retroativa (de baixo pra cima) -> Ux = y

Args:
    (const Matrix&) U: Matriz triangular superior;
    (const std::vector<double>&) y: Vetor.

Returns:
    (std::vector<double>): Vetor solução y
*/

// ========== Método via fatoração LU ==========
void decomposeLU(const Matrix& A, Matrix& L, Matrix& U);
/*
Fatora a matriz A e salva seus fatores em L e U.

Args:
    (const Matrix&) A: Matriz quadrada qualquer;
    (Matrix&) L: Matriz triangular inferior com diagonal unitária;
    (Matrix&) U: Matriz trianguler superior.
*/

std::vector<double> solveLU(const Matrix& L, const Matrix& U, const std::vector<double>& f);
/*
Realiza a resolução do sistema dado LU. Ly = f e Ux = y.

Args:
    (const Matrix&) L: Matriz triangular inferior com diagonal unitária;
    (const Matrix&) U: Matriz trianguler superior.
    (const std::vector<double>&) f: Vetor de termos independentes.
Returns:
    (std::vector<double): Vetor solução
*/

// ========== Método via fatoração LDP ==========
void decomposeLDP(const Matrix& A, Matrix& L, Matrix& D, Matrix& P);
/*
Fatora a matriz A e salva seus fatores em L, D e P.

Args:
    (const Matrix&) A: Matriz quadrada qualquer;
    (Matrix&) L: Matriz triangular inferior com diagonal unitária;
    (Matrix&) D: Matriz diagonal;
    (Matrix&) P: Matriz trianguler superior com diaognal unitária.
*/

std::vector<double> solveLDP(const Matrix& L, const Matrix& D, const Matrix& P, const std::vector<double>& f);
/*
Realiza a resolução do sistema dado LDP. Ly = f, Dz = y e Px = z.

Args:
    (const Matrix&) L: Matriz triangular inferior com diagonal unitária;
    (const Matrix&) D: Matriz diagonal;
    (const Matrix&) P: Matriz trianguler superior com diaognal unitária;
    (const std::vector<double>&) f: Vetor de termos independentes.
Returns:
    (std::vector<double): Vetor solução
*/

#endif
