#ifndef LINEAR_SYSTEM_SOLVER_HPP
#define LINEAR_SYSTEM_SOLVER_HPP

#include "matrix.hpp"
#include <vector>

class LinearSystemSolver {
private:
    static std::vector<double> forwardSubstitution(const Matrix& L, const std::vector<double>& b);
    static std::vector<double> backwardSubstitution(const Matrix& U, const std::vector<double>& y);

public:
    static void decomposeLU(const Matrix& A, Matrix& L, Matrix& U);
    static std::vector<double> solveLU(const Matrix& L, const Matrix& U, const std::vector<double>& f);

    static void decomposeLDP(const Matrix& A, Matrix& L, Matrix& D, Matrix& P);
    static std::vector<double> solveLDP(const Matrix& L, const Matrix& D, const Matrix& P, const std::vector<double>& f);
};

#endif
